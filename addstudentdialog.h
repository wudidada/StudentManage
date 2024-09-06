#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QDialogButtonBox)
QT_FORWARD_DECLARE_CLASS(QSqlRelationalTableModel)
QT_FORWARD_DECLARE_CLASS(QGroupBox)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QPushButton)

class AddStudentDialog : public QDialog
{
    Q_OBJECT

public:
    AddStudentDialog(QSqlRelationalTableModel *classModel, QWidget *parent = nullptr);

private slots:
    void addStudent();

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

#endif // ADDSTUDENTDIALOG_H
