#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
static bool createConnection()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
db.setHostName("localhost");
db.setDatabaseName("mydata");   //这里输入你的数据库名
db.setUserName("root");
db.setPassword("jzd123456");   //这里输入你的密码
if (!db.open()) {
QMessageBox::critical(0, QObject::tr("无法打开数据库"),
"无法创建数据库连接！ ", QMessageBox::Cancel);
return false;
}
//下面来创建表
// 如果 MySQL 数据库中已经存在同名的表， 那么下面的代码不会执行
QSqlQuery query(db);
// 使数据库支持中文
query.exec("SET NAMES 'Latin1'");

query.exec("create table user(userName varchar(20) NOT NULL unique,"
           "userPwd varchar(20) NOT NULL,usernum varchar(10) NOT NULL unique);");
query.exec("insert into course values('hhhhh', '123456', '2190120504')");
return true;
}
#endif // CONNECTION_H
