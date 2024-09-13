#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "studentquerymodel.h"
#include <QMainWindow>
#include <QTableView>
#include <QtSql>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showAddWindow();
    void showSearchWindow();
    void updateClassModel();
    void deleteStudent();
    void editStudent();

private:
    int classGradeIdx = 0, classNameIdx = 0, studentGradeIdx = 0, studentClassIdx = 0;

    QWidget *window = nullptr;

    QGridLayout *gridLayout = nullptr;

    StudentQueryModel *classModel = nullptr;
    QSqlRelationalTableModel *gradeModel = nullptr;
    QStandardItemModel *gradeTreeModel = nullptr;

    QTableView *classView = nullptr;
    QTreeView *gradeView = nullptr;

    QGroupBox *createGradeGroupBox();
    QGroupBox *createClassGroupBox();
    QGroupBox *createButtonGroupBox();

    QPushButton *addButton = nullptr;
    QPushButton *deleteButton = nullptr;
    QPushButton *editButton = nullptr;
    QPushButton *searchButton = nullptr;

    void createLayout();
    void createModel();
    void createTreeModel();
    void configureWidgets();
    void createMappings();
    void createMenuBar();
    void showClassStudents(const QModelIndex &index);

    void showError(const QString &title, const QString &message);
};
#endif // MAINWINDOW_H
