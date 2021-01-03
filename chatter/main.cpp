#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");//通过Mysql
    db.setHostName("localhost");//服务器地址
    db.setDatabaseName("mydata");//数据库名称
    db.setUserName("root");//账号名称
    db.setPort(3306);//端口号
    db.setPassword("jzd123456");//密码

    if(db.open())
    {
        qDebug()<<"数据库连接成功"<<endl;
        w.show();
    }
    else
    {
        QMessageBox::warning(NULL,"error","数据库连接失败");
        return 0;
    }

    return a.exec();
}
