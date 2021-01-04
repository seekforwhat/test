#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle(tr("交互界面"));
    //获取用户当前ipv4地址
    QString usrIPV4=getHostIpAddress();
    qDebug()<<usrIPV4;
}

login::~login()
{
    delete ui;
}

//用户使用按钮下线
void login::on_offButton_clicked()
{
    //offline 用于用户下线
    QString offline=QString("update user set status='false' where userName='%1';").arg(_ID);
    QSqlQuery query;
    query.exec(offline);
    QMessageBox::information(NULL, "成功下线", "下线！！！", QMessageBox::Yes);
    this->close();
}

//用户使用关闭窗口
void  login::closeEvent ( QCloseEvent * )
{
    if( QMessageBox::question(this,
                             tr("Quit"),
                             tr("你确定要下线吗？"),
                              QMessageBox::Yes, QMessageBox::No )
                   == QMessageBox::Yes){
        login::on_offButton_clicked();
    }
}

//获取用户IPV4地址

QString login::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取最后一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}
