#include "mainwindow.h"
#include "studentaddwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // create the central widget for the window
    window = new QWidget(this);
    setCentralWidget(window);

    createLayout();

    createModel();

    // Populate the model
    if (!gradeModel->select())
    {
        showError(tr("初始化数据库失败"), gradeModel->lastError().text());
        return;
    }

    createTreeModel();

    // 打印gradeModel 行列数
    qDebug() << "gradeModel->rowCount() = " << gradeModel->rowCount();
    qDebug() << "gradeModel->columnCount() = " << gradeModel->columnCount();
    // 打印classModel 行列数
    qDebug() << "classModel->rowCount() = " << classModel->rowCount();
    qDebug() << "classModel->columnCount() = " << classModel->columnCount();

    configureWidgets();

    // create the mappings between the UI elements and the SQL model
    // createMappings();

    // tableView->setCurrentIndex(model->index(0, 0));
    // tableView->selectRow(0);

    // createMenuBar();

    // connect(ui->AddButton, &QPushButton::clicked, this, &MainWindow::showAddWindow);
}

void MainWindow::createLayout()
{
    QGroupBox *grades = createGradeGroupBox();
    QGroupBox *classes = createClassGroupBox();
    QGroupBox *buttons = createButtonGroupBox();

    // artistView->setCurrentIndex(0);
    // Dialog::setInitialAlbumAndArtistId(model->rowCount(), artistView->count());

    // connect(model, &QSqlRelationalTableModel::rowsInserted,
    // this, &MainWindow::adjustHeader);
    // connect(model, &QSqlRelationalTableModel::rowsRemoved,
    // this, &MainWindow::adjustHeader);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(grades, 0, 0, 2, 1);
    layout->addWidget(buttons, 0, 1);
    layout->addWidget(classes, 1, 1);

    layout->setColumnStretch(1, 1);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    createMenuBar();

    // resize(850, 400);
    setWindowTitle(tr("学生信息管理系统"));
}

QGroupBox *MainWindow::createGradeGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("班级列表"));

    gradeView = new QTreeView;
    gradeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gradeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    gradeView->setSelectionMode(QAbstractItemView::SingleSelection);
    gradeView->setAlternatingRowColors(true);
    // gradeView->setModel(gradeModel);
    // adjustHeader();

    QLocale locale = gradeView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    gradeView->setLocale(locale);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(gradeView, 0, {});
    box->setLayout(layout);

    return box;
}

QGroupBox *MainWindow::createClassGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("学生信息"));

    classView = new QTableView;
    classView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    classView->setSortingEnabled(true);
    classView->setSelectionBehavior(QAbstractItemView::SelectRows);
    classView->setSelectionMode(QAbstractItemView::SingleSelection);
    classView->setShowGrid(false);
    classView->verticalHeader()->hide();
    classView->setAlternatingRowColors(true);
    classView->setModel(classModel);
    // adjustHeader();

    QLocale locale = classView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    classView->setLocale(locale);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(classView, 0, {});
    box->setLayout(layout);

    return box;
}

QGroupBox *MainWindow::createButtonGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("操作"));

    QPushButton *addButton = new QPushButton(tr("添加"));
    QPushButton *deleteButton = new QPushButton(tr("删除"));
    QPushButton *quitButton = new QPushButton(tr("退出"));

    connect(addButton, &QPushButton::clicked, this, &MainWindow::showAddWindow);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::showAddWindow);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::showAddWindow);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(addButton);
    layout->addWidget(deleteButton);
    layout->addWidget(quitButton);
    layout->addStretch(1);
    box->setLayout(layout);

    return box;
}

void MainWindow::createModel()
{
    gradeModel = new QSqlRelationalTableModel(gradeView);
    gradeModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    gradeModel->setTable("class");

    classGradeIdx = gradeModel->fieldIndex("grade");
    classNameIdx = gradeModel->fieldIndex("name");

    // Set the relations to the other database tables
    gradeModel->setRelation(classGradeIdx, QSqlRelation("grades", "grade", "name"));

    // // Set the localised header captions
    // gradeModel->setSort(classGradeIdx, Qt::AscendingOrder);

    classModel = new StudentQueryModel(classView);
    classModel->loadData();
}

void MainWindow::createTreeModel()
{
    gradeTreeModel = new QStandardItemModel(gradeView);
    // 遍历gradeModel，将数据插入到gradeTreeModel中
    for (int i = 0; i < gradeModel->rowCount(); i++)
    {
        QSqlRecord record = gradeModel->record(i);

        QString gradeName = record.value(classGradeIdx).toString();
        QString className = record.value(classNameIdx).toString();

        QStandardItem *gradeItem = nullptr;
        for (int j = 0; j < gradeTreeModel->rowCount(); j++)
        {
            if (gradeTreeModel->item(j)->text() == gradeName)
            {
                gradeItem = gradeTreeModel->item(j);
                break;
            }
        }

        if (gradeItem == nullptr)
        {
            gradeItem = new QStandardItem(gradeName);
            gradeTreeModel->appendRow(gradeItem);
        }

        gradeItem->appendRow(new QStandardItem(className));
    }
}

void MainWindow::configureWidgets()
{
    gradeTreeModel->setHorizontalHeaderLabels({tr("年级")});
    gradeView->setModel(gradeTreeModel);

    connect(gradeView, &QAbstractItemView::clicked,
            this, &MainWindow::showClassStudents);
    connect(gradeView, &QAbstractItemView::activated,
            this, &MainWindow::showClassStudents);

    // gradeView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::);

    // connect(gradeView, &QTableView::clicked,
    //         this, &MainWindow::showClassStudents);
    // connect(gradeView, &QTableView::activated,
    //         this, &MainWindow::showClassStudents);

    classView->setModel(classModel);
}

void MainWindow::showClassStudents(const QModelIndex &index)
{
    QString className, gradeName;

    if (index.parent().isValid())
    {
        className = gradeTreeModel->itemFromIndex(index)->text();
        gradeName = gradeTreeModel->itemFromIndex(index.parent())->text();
        classModel->loadClassData(className);
    }
    else
    {
        gradeName = gradeTreeModel->itemFromIndex(index)->text();
        classModel->loadGradeData(gradeName);
    }

    if (gradeName.isEmpty() || className.isEmpty())
    {
        return;
    }
}

void MainWindow::createMenuBar()
{
}

void MainWindow::showAddWindow()
{
    QWidget *addWindow = new StudentAddWindow(this);
    addWindow->show();
}

void MainWindow::showError(const QString &title, const QString &message)
{
    QMessageBox::critical(this, title, message);
}
