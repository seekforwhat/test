#include "myregister.h"
#include "ui_myregister.h"

myregister::myregister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myregister)
{
    ui->setupUi(this);
    setWindowTitle(tr("注册界面"));
    //标题处理
        //居中
        ui->title->setAlignment(Qt::AlignHCenter);
        //字体
        QFont font ( "Microsoft YaHei", 20, QFont::Bold);
        ui->title->setFont(font);
    //登录界面
        //居中
        ui->ID->setAlignment(Qt::AlignHCenter);
        ui->password->setAlignment(Qt::AlignHCenter);
        ui->again->setAlignment(Qt::AlignHCenter);
        ui->stdID->setAlignment(Qt::AlignHCenter);
        //字体
        QFont log_font ( "Microsoft YaHei", 10, QFont::Bold);
        ui->ID->setFont(log_font);
        ui->password->setFont(log_font);
        ui->again->setFont(log_font);
        ui->stdID->setFont(log_font);
        //提示信息
        ui->ID_Edit->setPlaceholderText("请输入3-10位英文字符");
        ui->password_Edit->setPlaceholderText("请输入6-12位字符");
        ui->again_Edit->setPlaceholderText("请再次输入密码");
        ui->stdID_Edit->setPlaceholderText("请输入9或10位学号");
        //密码格式
        ui->password_Edit->setEchoMode(QLineEdit::Password);
        ui->again_Edit->setEchoMode(QLineEdit::Password);
}

myregister::~myregister()
{
    delete ui;
}

void myregister::on_nakButton_clicked()
{
    this->close();
}

//注册界面
void myregister::on_ackButton_clicked()
{
    //--------------------------------------------------------
    QString _ID =ui->ID_Edit->text();
    QString _stdID = ui->stdID_Edit->text();
    QString Pword;
    QString _status="false";
    if(ui->password_Edit->text()==ui->again_Edit->text())
    {
        Pword =ui->password_Edit->text();
        //账号或密码不可为空
        if(_ID==""||Pword=="")
        {
            QMessageBox::information(this,"警告","账号或密码不可为空！",QMessageBox::Ok);
        }
        else
        {
            //对输入长度进行检查
            if(_ID.size()<3||_ID.size()>10)//判断用户名
            {
                QMessageBox::information(this,"警告","账号应为3-10位！",QMessageBox::Ok);
            }
            else if(Pword.size()<6||Pword.size()>12)//判断密码位数
            {
                QMessageBox::information(this,"警告","密码应为6-12位！",QMessageBox::Ok);
            }
            else if(_stdID.size()!=9&&_stdID.size()!=10)
            {
                QMessageBox::information(this,"警告","请输入正确的学号",QMessageBox::Ok);
            }
            //对输入字符进行检查
            if(IsEnglish(_ID))
            {
                qDebug()<<"全是英文，符合要求"<<endl;
                //insert 用于在数据库中建立账号
                QString insert=QString("insert into user values ('%1','%2','%3','%4'); ").arg(_ID).arg(Pword).arg(_stdID).arg(_status);
                //search 用于在数据库中查找未登录账号
                QString search=QString("select * from user where userName='%1' ").arg(_ID);
                QSqlQuery query;

                //数据库中userName、userNum的属性为unique;值相同会插入失败
                if(query.exec(insert))
                    QMessageBox::information(NULL, "注册成功", "注册成功！！！", QMessageBox::Yes);
                else if(query.exec(search)&&query.first())
                    QMessageBox::warning(NULL,"Error","账号重复，请重试！！！");
                else
                    QMessageBox::warning(NULL,"Error","学号重复，请重试！！！");
            }
            else
            {
                QMessageBox::information(this,"提示","账号需要是英文！",QMessageBox::Ok);
            }

        }
    }
    else
        QMessageBox::warning(NULL,"Error","密码不重复，请重试！！！");
}

//判断输入的字符是否全是英文
bool myregister::IsEnglish(QString &qstrSrc)
{
    QByteArray ba=qstrSrc.toLatin1();
    const char *s=ba.data();
    bool bret=true;

    while (*s) {
        if((*s>='A'&&*s<='Z')||(*s>='a'&&*s<='z'))
        {
        }
        else
        {
            bret=false;
            break;
        }
        s++;
    }
    return bret;
}

//设置背景
void myregister::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/background/sea.jpg"));
}
