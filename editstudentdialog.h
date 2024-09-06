#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include "addstudentdialog.h"
#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QDialogButtonBox)
QT_FORWARD_DECLARE_CLASS(QSqlRelationalTableModel)
QT_FORWARD_DECLARE_CLASS(QGroupBox)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QPushButton)

class EditStudentDialog : public AddStudentDialog
{
    Q_OBJECT

public:
    EditStudentDialog(const QString &name, const QString &gender, int id, const QString &grade, const QString &className, QWidget *parent = nullptr);

private slots:
    void commitEdit();
};

#endif // EDITSTUDENTDIALOG_H
