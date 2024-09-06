#include "editstudentdialog.h"

#include <QtSql>
#include <QtWidgets>

EditStudentDialog::EditStudentDialog(const QString &name, const QString &gender, int id, const QString &grade, const QString &className, QWidget *parent)
    : AddStudentDialog(nullptr, parent)
{
    nameEditor->setText(name);
    idEditor->setText(QString::number(id));
    genderEditor->setCurrentText(gender);
    gradeEditor->setCurrentText(grade);
    updateClassEditor(grade);
    classEditor->setCurrentText(className);

    setWindowTitle(tr("编辑学生信息"));

    connect(submitButton, &QPushButton::clicked, this, &EditStudentDialog::commitEdit);
}

void EditStudentDialog::commitEdit()
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
    query.prepare("UPDATE students SET name = :name, gender = :gender, class = :class WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":gender", gender);
    query.bindValue(":class", classId);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to update data." << query.lastError();
        reject();
    }
    else
    {
        accept();
    }
}
