#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
//for certification code
#include <QRegularExpression>
#include <QRegularExpressionValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    count=0;
    port=11111;
    server=new QTcpServer();
    server->listen(QHostAddress::Any,port);
    if(!server->isListening())
        qDebug()<<("Not Listening!");
    connect(server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));



    database = QSqlDatabase::addDatabase("QMYSQL");
//SQL connect to dorm
//    database.setHostName("140.113.146.173");
//    database.setDatabaseName("commodity");
//    database.setUserName("Aoop");
//    database.setPassword("1208");

//SQL localhost
    database.setHostName("localhost");
    database.setDatabaseName("commodity");
    database.setUserName("root");
    database.setPassword("a0989663205");
    database.setPassword("1234567");

    database.setPort(3306);
    bool ok = database.open();
    if(ok)
        qDebug()<<"SQl open successful";
    else
        qDebug()<<"cannot open";



    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();
    int minute = current_time.minute();
    int second = current_time.second();

    QString currentTime=QString::number(hour)+':'+QString::number(minute)+':'+QString::number(second);
    qDebug()<<currentTime;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::slotNewConnection()
{
    QTcpSocket *socket =server->nextPendingConnection();
    count++;
    QString s=QString::number(count)+" Welcome!\n";
    QByteArray writeBytes = s.toUtf8();
    writeBytes=s.toUtf8();
    socket->write(writeBytes);

    if(count<=3)
    {
        sockets.append(socket);
        connect(socket,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    }
    else
    {
        QString P="#Sorry!, full now\n";
    //    qDebug()<<count;
        QByteArray writeBytes = P.toUtf8();
        writeBytes=P.toUtf8();
        socket->write(writeBytes);
    }


}

//有人送指令到server
void MainWindow::slotReadyRead()
{
    QTcpSocket *socketR=dynamic_cast<QTcpSocket*>(sender());

    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();
    int minute = current_time.minute();
    int second = current_time.second();
    QString currentTime='['+QString::number(hour)+':'+QString::number(minute)+':'+QString::number(second)+"] ";


    if(socketR->canReadLine())
    {
        QByteArray readBytes=socketR->readLine().trimmed();
        QString readStr=QString::fromUtf8(readBytes);
        QString SeMesgOnBrowser="$"+currentTime+readStr;
        ui->textBrowser->append(SeMesgOnBrowser);


        if(readStr.startsWith("Login"))   //Login/username
        {
            socketname.push_back(readStr.mid(6));
        }
        else if(readStr.startsWith("Message")) //Message/username/whotochat/content
        {
            QStringList list=readStr.split("/");
//            list[1] from   list[2] to   list[3] content
            ui->textBrowser->append("split:");
            ui->textBrowser->append("command: "+list[0]);
            ui->textBrowser->append("from: "+list[1]);
            ui->textBrowser->append("to: "+list[2]);
            ui->textBrowser->append("content: "+list[3]);
            //找寄給誰
            QTcpSocket* sendto;
            for(int i=0;i<sockets.size();i++)
            {
                if(socketname[i]==list[2])
                    sendto=sockets[i];
            }

            QString sentString ="Message/"+list[1]+" says: "+list[3]+'\n';
            QByteArray writeByte=sentString.toUtf8();
            sendto->write(writeByte);
        }
        else
        {
            QString sentString ="You say: "+readStr+'\n';  //開始位置
            QByteArray writeByte=sentString.toUtf8();
            socketR->write(writeByte);
        }

        //以下會出現很多 if else　判斷傳來的訊息是啥　使用!strcmp....
//        QString sentString ="\nHello!\n";
//        QByteArray writeByte=sentString.toUtf8();
//        socketR->write(writeByte);


    }
}
void MainWindow::slotDisconnected()
{
    QTcpSocket *socketR=dynamic_cast<QTcpSocket*>(sender());

    ui->textBrowser->append("Disconnected!");
    if(sockets.contains(socketR))
        sockets.removeOne(socketR);
    socketR->deleteLater();
}

