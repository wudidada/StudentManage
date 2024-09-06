#include "addstudentdialog.h"

#include <QtSql>
#include <QtWidgets>

AddStudentDialog::AddStudentDialog(QSqlRelationalTableModel *classModel, QWidget *parent)
    : QDialog(parent)
{
    model = classModel;

    QGroupBox *inputWidgetBox = createInputWidgets();
    QDialogButtonBox *buttonBox = createButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(inputWidgetBox);
    layout->addWidget(buttonBox);
    setLayout(layout);

    setWindowTitle(tr("添加学生"));

    connect(submitButton, &QPushButton::clicked, this, &AddStudentDialog::addStudent);
    connect(closeButton, &QPushButton::clicked, this, &AddStudentDialog::close);
}

QGroupBox *AddStudentDialog::createInputWidgets()
{
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
    classEditor = new QLineEdit;

    genderEditor->addItem(tr("男"));
    genderEditor->addItem(tr("女"));
    gradeEditor->addItem(tr("一年级"));
    gradeEditor->addItem(tr("二年级"));
    gradeEditor->addItem(tr("三年级"));
    gradeEditor->addItem(tr("四年级"));
    gradeEditor->addItem(tr("五年级"));
    gradeEditor->addItem(tr("六年级"));

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

QDialogButtonBox *AddStudentDialog::createButtons()
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
    int classId = classEditor->text().toInt();

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
