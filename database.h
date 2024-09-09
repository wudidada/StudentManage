// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName(":memory:");
    db.setDatabaseName("student.db");
    if (!db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;

    // 如果表存在则略过
    if (db.tables().contains("grades", Qt::CaseInsensitive))
    {
        qDebug() << "Table grades already exists";
        return true;
    }

    query.exec("create table grades (grade int primary key,"
               "name varchar(20)) ");

    query.exec("insert into grades values(1, '一年级')");
    query.exec("insert into grades values(2, '二年级')");
    query.exec("insert into grades values(3, '三年级')");
    query.exec("insert into grades values(4, '四年级')");
    query.exec("insert into grades values(5, '五年级')");
    query.exec("insert into grades values(6, '六年级')");

    query.exec("create table class (id int primary key, "
               "name varchar(20), "
               "grade int)");

    query.exec("insert into class values(0, '1401', 1)");
    query.exec("insert into class values(1, '1402', 1)");
    query.exec("insert into class values(2, '1403', 1)");
    query.exec("insert into class values(3, '1404', 1)");
    query.exec("insert into class values(4, '1405', 1)");
    query.exec("insert into class values(5, '1406', 1)");

    query.exec("insert into class values(6, '1301', 2)");
    query.exec("insert into class values(7, '1302', 2)");
    query.exec("insert into class values(8, '1303', 2)");
    query.exec("insert into class values(9, '1304', 2)");
    query.exec("insert into class values(10, '1305', 2)");
    query.exec("insert into class values(11, '1306', 2)");

    query.exec("insert into class values(12, '1201', 3)");
    query.exec("insert into class values(13, '1202', 3)");
    query.exec("insert into class values(14, '1203', 3)");
    query.exec("insert into class values(15, '1204', 3)");
    query.exec("insert into class values(16, '1205', 3)");

    query.exec("insert into class values(17, '1101', 4)");
    query.exec("insert into class values(18, '1102', 4)");
    query.exec("insert into class values(19, '1103', 4)");
    query.exec("insert into class values(20, '1104', 4)");

    query.exec("insert into class values(21, '1001', 5)");
    query.exec("insert into class values(22, '1002', 5)");
    query.exec("insert into class values(23, '1003', 5)");

    query.exec("insert into class values(24, '0901', 6)");
    query.exec("insert into class values(25, '0902', 6)");

    query.exec("create table students (id int primary key, "
               "name varchar(20), "
               "gender varchar(2), "
               "class int)");

    query.exec("insert into students values(1, '张三', '男', 0)");
    query.exec("insert into students values(2, '李四', '女', 1)");
    query.exec("insert into students values(3, '王五', '男', 2)");
    query.exec("insert into students values(4, '赵六', '女', 3)");
    query.exec("insert into students values(5, '孙七', '男', 4)");
    query.exec("insert into students values(6, '周八', '女', 5)");
    query.exec("insert into students values(7, '吴九', '男', 6)");
    query.exec("insert into students values(8, '郑十', '女', 7)");
    query.exec("insert into students values(9, '冯十一', '男', 8)");
    query.exec("insert into students values(10, '陈十二', '女', 9)");
    query.exec("insert into students values(11, '褚十三', '男', 10)");
    query.exec("insert into students values(12, '卫十四', '女', 11)");
    query.exec("insert into students values(13, '蒋十五', '男', 12)");
    query.exec("insert into students values(14, '沈十六', '女', 13)");
    query.exec("insert into students values(15, '韩十七', '男', 14)");
    query.exec("insert into students values(16, '杨十八', '女', 15)");
    query.exec("insert into students values(17, '朱十九', '男', 16)");
    query.exec("insert into students values(18, '秦二十', '女', 17)");
    query.exec("insert into students values(19, '尤二十一', '男', 18)");
    query.exec("insert into students values(20, '许二十二', '女', 19)");
    query.exec("insert into students values(21, '何二十三', '男', 20)");
    query.exec("insert into students values(22, '吕二十四', '女', 21)");
    query.exec("insert into students values(23, '施二十五', '男', 22)");
    query.exec("insert into students values(24, '张二十六', '女', 23)");
    query.exec("insert into students values(25, '孔二十七', '男', 24)");
    query.exec("insert into students values(26, '曹二十八', '女', 25)");

    return true;
}

#endif
