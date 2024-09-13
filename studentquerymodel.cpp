#include "studentquerymodel.h"

#include <QtSql>

void StudentQueryModel::sort(int column, Qt::SortOrder order)
{
    QString orderByClause;

    switch (column)
    {
    case 0:
        orderByClause = "姓名";
        break;
    case 1:
        orderByClause = "性别";
        break;
    case 2:
        orderByClause = "学号";
        break;
    case 3:
        orderByClause = "班级";
        break;
    case 4:
        orderByClause = "年级";
        break;
    default:
        return; // 如果列索引无效，直接返回
    }

    sortStr = QString(" ORDER BY %1 %2").arg(orderByClause).arg((order == Qt::AscendingOrder) ? "ASC" : "DESC");
    loadData();
}

bool StudentQueryModel::loadData()
{
    setQuery(fullQueryStr());
    return lastError().type() == QSqlError::NoError;
}

bool StudentQueryModel::loadClassData(QString className)
{
    filterStr = QString(" WHERE 班级 = '%1' ").arg(className);
    loadData();
}

bool StudentQueryModel::loadGradeData(QString gradeName)
{
    filterStr = QString(" WHERE 年级 = '%1' ").arg(gradeName);
    loadData();
}

QString StudentQueryModel::fullQueryStr() const
{
    return queryStr + filterStr + sortStr;
}

void StudentQueryModel::searchByName(const QString &name)
{
    filterStr = QString(" WHERE 姓名 LIKE '%%1%' ").arg(name);
    loadData();
}

void StudentQueryModel::searchById(int id)
{
    filterStr = QString(" WHERE 学号 = %1 ").arg(id);
    loadData();
}
