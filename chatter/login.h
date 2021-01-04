#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork/QNetworkInterface>

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
    QString _ID;
    //获取IPV4地址
    QString getHostIpAddress();

private slots:
    void on_offButton_clicked();

private:
    Ui::login *ui;
    void closeEvent ( QCloseEvent * e );
};

#endif // LOGIN_H
