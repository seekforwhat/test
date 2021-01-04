# chatter app  

* 建立数据库中的user表  

```
create table user(userName varchar(20) NOT NULL unique,userPwd varchar(20) NOT NULL, 
usernum varchar(20) NOT NULL unique,status varchar(20) not null,friendsNum int(20) not null default 0, 
friends varchar(1100) default null);
```  

现在数据库的名字是temp 

这里NOT NULL限制不能为空，unique限制了唯一性

* 待完成的工作 
 > IPV4的存取与交互
 > 好友拉取窗口
 > 双击好友即可通信（同时在线的情况）
 > 将主机通信的cpp源码在QT中实现
