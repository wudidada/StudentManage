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
    EditStudentDialog(QSqlRelationalTableModel *classModel, QWidget *parent = nullptr);

private slots:
    void editStudent();

private:
    QSqlRelationalTableModel *model;

    QGroupBox *createInputWidgets();
    QDialogButtonBox *createButtons();

    QLineEdit *nameEditor;
    QLineEdit *idEditor;
    QComboBox *genderEditor;
    QComboBox *gradeEditor;
    QLineEdit *classEditor;

    QPushButton *submitButton;
    QPushButton *closeButton;
};

#endif // EDITSTUDENTDIALOG_H
