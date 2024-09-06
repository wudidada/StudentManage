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
protected slots:
    void updateClassEditor(const QString &grade);

protected:
    QLineEdit *nameEditor;
    QLineEdit *idEditor;
    QComboBox *genderEditor;
    QComboBox *gradeEditor;
    QComboBox *classEditor;

    QPushButton *submitButton;

private:
    QMap<QString, QList<QPair<int, QString>>> *gradeClassMap;
    QSqlRelationalTableModel *model;

    QMap<QString, QList<QPair<int, QString>>> *createGradeClassMap();
    QGroupBox *createInputWidgets();
    QDialogButtonBox *createButtons();

    QPushButton *closeButton;
};

#endif // ADDSTUDENTDIALOG_H
