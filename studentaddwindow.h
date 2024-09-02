#ifndef STUDENTADDWINDOW_H
#define STUDENTADDWINDOW_H

#include <QWidget>

namespace Ui {
class StudentAddWindow;
}

class StudentAddWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentAddWindow(QWidget *parent = nullptr);
    ~StudentAddWindow();

private slots:
    void addStudent();

private:
    Ui::StudentAddWindow *ui;
};

#endif // STUDENTADDWINDOW_H
