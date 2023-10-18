#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <qdatetime.h>
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    QString getmesg();
    void writeMesgToServer(QString mes);
signals:
    void chatroommesg();
private:
    QTcpSocket *socket;
    int timeout;
    unsigned short port;
    QString hostname;

    QString mesg;
    bool firstconnect;
    int number;
    int sendto;
    bool over=false;





private slots:
    void slotReadyRead();

    void slotDisconnected();
//    void on_pushButton_clicked();
//    void on_radioButton_clicked();
//    void on_radioButton_2_clicked();
//    void on_radioButton_3_clicked();
//    void on_radioButton_4_clicked();
};

#endif // CLIENT_H
