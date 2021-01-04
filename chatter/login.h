#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork/QNetworkInterface>
#include <QtEvents>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    //登录的账号
    QString myID;
    //获取IPV4地址
    QString getHostIpAddress();
    //添加好友
    void AddFriend(QString new_firend);

private slots:
    void on_offButton_clicked();

    void on_search_Button_clicked();

private:
    Ui::login *ui;
    void closeEvent ( QCloseEvent * event);
};

#endif // LOGIN_H
