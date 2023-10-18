#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}
{
    hostname="127.0.0.1";
    port=11111;

    socket=new QTcpSocket();
    socket->connectToHost(hostname,port);

    timeout=10000;
    if(!socket->waitForConnected(timeout))
    {
        qDebug()<<"Unable to connect to server!";
        qDebug()<<QString::number(socket->error());

    }
    else
         qDebug()<<"connect to server!";


    connect(socket,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    QString writeStr="Hellow Server\n";
    QByteArray writeByte=writeStr.toUtf8();
    socket->write(writeByte);

    firstconnect=true;

}

void Client::writeMesgToServer(QString mes)
{
    QString writeStr=mes+="\n";
    QByteArray writeByte=writeStr.toUtf8();
    socket->write(writeByte);
}

void Client::slotReadyRead()
{
//    QTcpSocket *socket=dynamic_cast<QTcpSocket*>(sender());
//    qDebug()<<socket->canReadLine();  //印出true


    while(socket->canReadLine())  //!!LIne!!!!
    {

        QByteArray readBytes=socket->readLine().trimmed();
        QString readStr=QString::fromUtf8(readBytes);

        qDebug()<<"Server :" +readStr;

        if(readStr.startsWith("Message"))
        {
            mesg=readStr.mid(8);
//            qDebug()<<currentTime+mesg;
            emit chatroommesg();
        }

    }
}
QString Client::getmesg()
{
    return mesg;
}
void Client::slotDisconnected()
{
    if(over==false)
    {emit disconnect();
    }
//        ui->textBrowser->append("Disconnected!");
    over=true;
    socket->deleteLater();
}
