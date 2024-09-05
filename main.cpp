#include "mainwindow.h"

#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection())
        return EXIT_FAILURE;

    MainWindow w;
    w.show();
    return a.exec();
}
