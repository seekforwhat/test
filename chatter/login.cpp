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
    QString offline=QString("update user set status='false' where userName='%1';").arg(myID);
    QSqlQuery query;
    query.exec(offline);
    this->close();
}

//用户使用关闭窗口
void  login::closeEvent ( QCloseEvent * event )
{
    if( QMessageBox::question(this,tr("Quit"),tr("你确定要下线吗？"),
        QMessageBox::Yes, QMessageBox::No)== QMessageBox::Yes)
    {
        login::on_offButton_clicked();
    }
    else
        event->ignore();
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

//搜索用户
void login::on_search_Button_clicked()
{
    QString _ID=ui->search_Edit->text();
    QString search=QString("select * from user where userName='%1' ").arg(_ID);
    QSqlQuery query;
    if(query.exec(search))
    {
        if( QMessageBox::question(this,tr("好友搜索"),tr("该用户存在，是否添加其为好友？"),
            QMessageBox::Yes, QMessageBox::No)== QMessageBox::Yes)
        {
            query.next();
            QString new_friend=query.value(0).toString();
            AddFriend(new_friend);
        }
    }
}

//添加好友
void login::AddFriend(QString new_firend)
{
    if(new_firend==this->myID)
    {
        QMessageBox::warning(NULL,"Error","这是您本人的账号！！！");
        return;
    }
    //如果好友数量为零使用add_firstfriend,反之则使用add_friend
    QString add_friend=QString("UPDATE user SET friends = CONCAT(friends,'%1')"
                               "WHERE userName = '%2'").arg(new_firend+',').arg(this->myID);
    QString add_firstfriend=QString("UPDATE user SET friends = '%1' WHERE userName = '%2'").arg(new_firend+',').arg(this->myID);
    //asknum 用于查询现有好友数
    QString asknum=QString("select friendsNum from user where userName='%1'").arg(this->myID);
    //if_duplicate 用于查询是否已经添加好友
    QString if_duplicate=QString("select '%1' from user where userName='%2'").arg(new_firend+',').arg(this->myID);
    QSqlQuery query;
    query.exec(asknum);
    query.next();
    //取出用户现有的好友数
    int friend_num=query.value(0).toInt();
    //好友数上限为100人
    if(friend_num==100)
    {
        QMessageBox::warning(NULL,"Error","好友数已达上限！！！");
        return;
    }
    if(friend_num==0)
    {
        query.exec(add_firstfriend);
        friend_num++;
        //add_friendnum 用于好友数自增
        QString add_friendnum=QString("UPDATE user SET friendsNum = '%1' WHERE userName = '%2'").arg(friend_num).arg(this->myID);
        query.exec(add_friendnum);
    }
    else
    {
        query.exec(if_duplicate);
        if(query.first())
        {
            QMessageBox::warning(NULL,"Error","您已经添加其为好友！！！");
            return;
        }
        query.exec(add_friend);
        friend_num++;
        //add_friendnum 用于好友数自增
        QString add_friendnum=QString("UPDATE user SET friendsNum = '%1' WHERE userName = '%2'").arg(friend_num).arg(this->myID);
        query.exec(add_friendnum);
    }
}
