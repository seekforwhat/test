#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//SQL头文件
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

//子窗口
#include "login.h"
#include "myregister.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_my_login_clicked();

    void on_my_register_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
