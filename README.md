# chatter app
## 建立数据库中的user表
命令：
create table user(userName varchar(20) NOT NULL unique,userPwd varchar(20) NOT NULL,usernum varchar(20) NOT NULL unique,status varchar(20) not null;);
这里NOT NULL限制不能为空，unique限制了唯一性
