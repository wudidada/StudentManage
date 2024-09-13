#include "searchstudentdialog.h"

#include <QtSql>
#include <QtWidgets>

SearchStudentDialog::SearchStudentDialog(QWidget *parent)
    : QDialog(parent)
{
    QGroupBox *searchBox = createSearchGroupBox();
    QGroupBox *resultBox = createResultGroupBox();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(searchBox);
    layout->addWidget(resultBox);
    setLayout(layout);

    model = new StudentQueryModel(resultView);
    model->loadData();
    resultView->setModel(model);

    setWindowTitle(tr("搜索学生"));

    resize(resultView->horizontalHeader()->length(), 400);

    connect(searchByIdButton, &QPushButton::clicked, this, &SearchStudentDialog::searchById);
    connect(searchByNameButton, &QPushButton::clicked, this, &SearchStudentDialog::searchByName);
}

QGroupBox *SearchStudentDialog::createSearchGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("搜索条件"));

    QLabel *nameLabel = new QLabel(tr("姓名:"));
    QLabel *idLabel = new QLabel(tr("学号:"));

    nameEditor = new QLineEdit;
    idEditor = new QLineEdit;

    searchByIdButton = new QPushButton(tr("按学号搜索"));
    searchByNameButton = new QPushButton(tr("按姓名搜索"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameEditor, 0, 1);
    layout->addWidget(searchByNameButton, 0, 2);
    layout->addWidget(idLabel, 1, 0);
    layout->addWidget(idEditor, 1, 1);
    layout->addWidget(searchByIdButton, 1, 2);

    box->setLayout(layout);
    return box;
}

QGroupBox *SearchStudentDialog::createResultGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("搜索结果"));

    resultView = new QTableView;
    resultView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resultView->setSortingEnabled(true);
    resultView->setSelectionBehavior(QAbstractItemView::SelectRows);
    resultView->setSelectionMode(QAbstractItemView::SingleSelection);
    resultView->setShowGrid(false);
    resultView->verticalHeader()->hide();
    resultView->setAlternatingRowColors(true);
    resultView->setModel(model);

    QLocale locale = resultView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    resultView->setLocale(locale);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(resultView, 0, {});
    box->setLayout(layout);

    return box;
}

void SearchStudentDialog::searchById()
{
    int id = idEditor->text().toInt();

    model->searchById(id);
}

void SearchStudentDialog::searchByName()
{
    QString name = nameEditor->text();

    model->searchByName(name);
}
