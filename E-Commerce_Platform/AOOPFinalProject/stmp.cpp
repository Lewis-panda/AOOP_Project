#include "stmp.h"

Stmp::Stmp(QObject *parent)
    : QObject{parent}
{
    serverIP="smtp-relay.gmail.com";
    conntoLewis="lewisss.com";
    password="pocikiajuoczfgoy";
    username="lewis@lewisss.com";
    sslSocket=new QSslSocket;
    connect(sslSocket, SIGNAL(connected()), this, SLOT(connectToServer()));
    connect(sslSocket, SIGNAL(disconnected()), this, SLOT(disconnectFromServer()));
    connect(sslSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));
    //    qDebug()<<QSslSocket::sslLibraryBuildVersionString();
    //    qDebug() << QSslSocket::supportsSsl();


    int number;
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<6;i++)
    {
        number=rand()%10;
        VertifyCode.append(QString::number(number));
    }
    qDebug()<<"Initialize!";
}

QString Stmp::getVertifyCode()
{
    return VertifyCode;
}
Stmp::~Stmp()
{
    delete sslSocket;
}
void Stmp::sendEmail(QString to, QString title, QString text)
{
    this->to=to;
    this->title = title;
    this->text = text;
    sslSocket->abort();
    serverText.clear();
    status = 0;
    sslSocket->connectToHostEncrypted(serverIP, 465);
}

void Stmp::connectToServer()
{
    qDebug()<<"connect to server";
}

void Stmp::disconnectFromServer()
{
    qDebug()<<"disconnect from server";
    emit disconnected();
}


#define STATUS_MAX 7
void Stmp::getMessage()
{
    QByteArray curText = sslSocket->readAll();
    serverText.append(curText);
    QByteArray text;
//    qDebug()<<"status"<<status;
//    qDebug()<<curText;
    if(serverText.indexOf("Error")!=-1 || serverText.indexOf("503")!=-1)
    {
        //出错了
        qDebug()<<"get the Error message";
        //        sslSocket->disconnectFromHost();
        emit disconnected();
        return ;
    }
    if(status==5 && serverText.indexOf("250")!=-1)
    {
        //登出

        text.append("QUIT\r\n");
        status = 6;
    }
    else if(status==4 && serverText.indexOf("354")!=-1)
    {
        //
        //        text.append("Subject:=?utf-8?B?");
        text.append("Subject: ");
        text.append(QByteArray().append(title.toUtf8()));
        text.append("\r\n");
        text.append("To: ");
        text.append(QByteArray().append(to.toUtf8()));
        text.append("\r\nFrom: ");
        QString test="ShopooA";
        text.append(QByteArray().append(test.toUtf8()));
        //        text.append(QByteArray().append(username.toUtf8()));
        text.append(" <");
        text.append(QByteArray().append(username.toUtf8()));
        text.append(">\r\n");
        text.append("Content-Type: text/plain; charset=UTF8;\r\n");
        text.append("Content-Transfer-Encoding: 7BIT\r\n\r\n");
        QString t = this->text;
        t.replace("\n", "\r\n").replace("\r\n.\r\n", "\r\n..\r\n");
        text.append(QByteArray().append(t.toUtf8()));
        text.append("\r\n.\r\n");
        status = 5;
    }
    else if(status==3 && serverText.indexOf("250")!=-1)
    {
        //DATA
        text.append("DATA\r\n");
        status = 4;
    }
    else if(status==2 && serverText.indexOf("235")!=-1)
    {
        //Sender and Receiver
        text.append("MAIL FROM: <");
        text.append(QByteArray().append(username.toUtf8()));
        text.append(">\r\n");
        text.append("RCPT TO: <");
        text.append(QByteArray().append(to.toUtf8()));
        text.append(">\r\n");
        status = 3;
    }
    else if(status==7 && serverText.indexOf("334")!=-1)
    {
        //登入密碼
        text.append(QByteArray().append(password.toUtf8().toBase64()));
        text.append("\r\n");
        status = 2;
    }
    else if(status==1 && serverText.indexOf("334")!=-1)
    {
        //登入的帳號
        text.append(QByteArray().append(username.toUtf8().toBase64()));
        text.append("\r\n");
        status = 7;
    }
    else if(status==0 && serverText.indexOf("220")!=-1)
    {
        text.append("EHLO ");
        text.append(QByteArray().append(conntoLewis.toUtf8()));
        text.append("\r\nAUTH LOGIN\r\n");
        status = 1;
    }


    sslSocket->write(text);
    //qDebug()<<text;
    if(status == 6)
    {
        qDebug()<<"Email has send!\n";
        sslSocket->disconnectFromHost();
    }
}

//void Stmp::sendEmailSlot(QString to, QString title, QString text)
//{
//    sendEmail(to, title, text);
//}
void Stmp::sendVertifyCodeSlot(QString to)
{
    title="Vertify Code From shopooA!";
    text="Hello!\n \nYour Vertifiy code is :\n\n\t\t\t";
    text.append(VertifyCode);
    text.append("\n\nPlease using the code to vertify your account!\n");
    text.append("\nThanks for your Registration!!\n");
    text.append("\nFrom : ShopooA\n");
    text.append("\n-----------------------------------------------\n");
    text.append("\nAny Question?\n");
    text.append("\nPhone : 0966006717\n");
    text.append("\nEmail : lewis@lewisss.com\n");
    text.append("\nContact us whenever you want.\n");
    text.append("\n-----------------------------------------------\n");
    sendEmail(to, title, text);
}


