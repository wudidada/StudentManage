#ifndef SEARCHSTUDENTDIALOG_H
#define SEARCHSTUDENTDIALOG_H

#include <QDialog>
#include "studentquerymodel.h"

QT_FORWARD_DECLARE_CLASS(QDialogButtonBox)
QT_FORWARD_DECLARE_CLASS(QSqlRelationalTableModel)
QT_FORWARD_DECLARE_CLASS(QGroupBox)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QTableView)

class SearchStudentDialog : public QDialog
{
    Q_OBJECT

public:
    SearchStudentDialog(QWidget *parent = nullptr);

private slots:
    void searchByName();
    void searchById();

private:
    QLineEdit *nameEditor;
    QLineEdit *idEditor;

    QPushButton *searchByNameButton;
    QPushButton *searchByIdButton;

    QTableView *resultView;

    QGroupBox *createSearchGroupBox();
    QGroupBox *createResultGroupBox();

    StudentQueryModel *model;
};

#endif // SEARCHSTUDENTDIALOG_H
