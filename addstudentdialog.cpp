#include "addstudentdialog.h"

#include <QtSql>
#include <QtWidgets>

AddStudentDialog::AddStudentDialog(QSqlRelationalTableModel *gradeModel, QWidget *parent)
    : QDialog(parent)
{
    model = gradeModel;

    QGroupBox *inputWidgetBox = createInputWidgets();
    QDialogButtonBox *buttonBox = createButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(inputWidgetBox);
    layout->addWidget(buttonBox);
    setLayout(layout);

    setWindowTitle(tr("添加学生"));

    connect(submitButton, &QPushButton::clicked, this, &AddStudentDialog::addStudent);
    connect(closeButton, &QPushButton::clicked, this, &AddStudentDialog::close);

    connect(gradeEditor, &QComboBox::currentTextChanged, this, &AddStudentDialog::updateClassEditor);
}

QGroupBox *AddStudentDialog::createInputWidgets()
{
    gradeClassMap = createGradeClassMap();

    QGroupBox *box = new QGroupBox(tr("输入学生信息"));

    QLabel *nameLabel = new QLabel(tr("姓名:"));
    QLabel *idLabel = new QLabel(tr("学号:"));
    QLabel *genderLabel = new QLabel(tr("性别:"));
    QLabel *gradeLabel = new QLabel(tr("年级:"));
    QLabel *classLabel = new QLabel(tr("班级:"));

    nameEditor = new QLineEdit;
    idEditor = new QLineEdit;
    genderEditor = new QComboBox;
    gradeEditor = new QComboBox;
    classEditor = new QComboBox;

    genderEditor->addItem(tr("男"));
    genderEditor->addItem(tr("女"));

    for (auto it = gradeClassMap->begin(); it != gradeClassMap->end(); it++)
    {
        gradeEditor->addItem(it.key());
    }

    updateClassEditor(gradeEditor->currentText());

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameEditor, 0, 1);
    layout->addWidget(idLabel, 1, 0);
    layout->addWidget(idEditor, 1, 1);
    layout->addWidget(genderLabel, 2, 0);
    layout->addWidget(genderEditor, 2, 1);
    layout->addWidget(gradeLabel, 3, 0);
    layout->addWidget(gradeEditor, 3, 1);
    layout->addWidget(classLabel, 4, 0);
    layout->addWidget(classEditor, 4, 1);

    box->setLayout(layout);
    return box;
}

QMap<QString, QList<QPair<int, QString>>> *AddStudentDialog::createGradeClassMap()
{
    QMap<QString, QList<QPair<int, QString>>> *map = new QMap<QString, QList<QPair<int, QString>>>();

    QSqlQueryModel queryModel;
    queryModel.setQuery("SELECT grades.name 年级, class.id class_id, class.name 班级 "
                        "FROM class "
                        "LEFT JOIN grades "
                        "ON class.grade = grades.grade");

    if (queryModel.lastError().isValid())
    {
        qDebug() << "Error: Failed to query data." << queryModel.lastError();
        return map;
    }

    // 从view中获取数据
    for (int i = 0; i < queryModel.rowCount(); i++)
    {
        QSqlRecord record = queryModel.record(i);

        QString gradeName = record.value("年级").toString();
        QString className = record.value("班级").toString();
        int classId = record.value("class_id").toInt();

        // qDebug() << "gradeName: " << gradeName << " className: " << className << " classId: " << classId;

        if (!map->contains(gradeName))
        {
            QList<QPair<int, QString>> list;
            list.append(qMakePair(classId, className));
            map->insert(gradeName, list);
        }
        else
        {
            QList<QPair<int, QString>> list = map->value(gradeName);
            list.append(qMakePair(classId, className));
            map->insert(gradeName, list);
        }
    }

    return map;
}

void AddStudentDialog::updateClassEditor(const QString &grade)
{
    classEditor->clear();

    QList<QPair<int, QString>> list = gradeClassMap->value(grade);
    for (int i = 0; i < list.size(); i++)
    {
        classEditor->addItem(list.at(i).second, list.at(i).first);
    }
}

QDialogButtonBox *
AddStudentDialog::createButtons()
{
    submitButton = new QPushButton(tr("提交"));
    closeButton = new QPushButton(tr("关闭"));

    closeButton->setDefault(true);

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(submitButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}

void AddStudentDialog::addStudent()
{
    // 姓名 学号 性别 年级 班级
    QString name = nameEditor->text();
    int id = idEditor->text().toInt();
    QString gender = genderEditor->currentText();
    int classId = classEditor->currentData().toInt();

    qDebug() << "name: " << name << " id: " << id << " gender: " << gender << " class: " << classId;

    if (name.isEmpty())
    {
        qDebug() << "请输入完整的信息";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO students (id, name, gender, class) VALUES (:id, :name, :gender, :class)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":gender", gender);
    query.bindValue(":class", classId);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to insert data." << query.lastError();
        reject();
    }
    else
    {
        accept();
    }
}
