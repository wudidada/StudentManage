#ifndef STUDENTQUERYMODEL_H
#define STUDENTQUERYMODEL_H

#include <QSqlQueryModel>

class StudentQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    using QSqlQueryModel::QSqlQueryModel;
    void sort(int column, Qt::SortOrder order);
    void loadData();
    void loadClassData(QString className);
    void loadGradeData(QString gradeName);
    void searchByName(const QString &name);
    void searchById(const int id);

private:
    const QString queryStr = "SELECT students.name 姓名, gender 性别, students.id 学号, class.name 班级, grades.name 年级 "
                             "FROM students "
                             "LEFT JOIN class ON students.class = class.id "
                             "LEFT JOIN grades ON class.grade = grades.grade";
    QString filterStr;
    QString sortStr;

    QString fullQueryStr() const;
};

#endif // STUDENTQUERYMODEL_H