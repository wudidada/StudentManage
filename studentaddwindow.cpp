#include "studentaddwindow.h"
#include "ui_studentaddwindow.h"

#include <QtSql>

StudentAddWindow::StudentAddWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentAddWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("添加学生"));

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    connect(ui->addButton, &QPushButton::clicked, this, &StudentAddWindow::addStudent);
    connect(ui->cancelButton, &QPushButton::clicked, this, &StudentAddWindow::close);
}

StudentAddWindow::~StudentAddWindow()
{
    delete ui;
}

void StudentAddWindow::addStudent()
{
    // 校验无误则退出窗口

    // 连接SQLite数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("formdata.db");

    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database." << db.lastError();
    } else {
        // 创建表格
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER PRIMARY KEY, name TEXT, stu_id INTERGER, gender INTEGER, grade INTEGER, class INTERGER)");
    }

    // 插入数据
    // 姓名 学号 性别 年级 班级
    QString name = ui->nameEdit->text();
    int id = ui->idEdit->text().toInt();
    int gender = ui->idEdit->text().toInt();
    int grade = ui->gradeEdit->text().toInt();
    int _class = ui->classEdit->text().toInt();


    if (name.isEmpty()) {
        qDebug() << "请输入完整的信息";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO person (name, stu_id, gender, grade, class) VALUES (:name, :id, :gender, :grade, :class)");
    query.bindValue(":id", id);
    query.bindValue(":gender", gender);
    query.bindValue(":grade", grade);
    query.bindValue(":class", _class);


    if (!query.exec()) {
        qDebug() << "Error: Failed to insert data." << query.lastError();
    } else {
        qDebug() << "数据已成功插入";
        // 清空输入框
        ui->nameEdit->clear();
    }


    // 校验有误则弹窗 不退出窗口

}

