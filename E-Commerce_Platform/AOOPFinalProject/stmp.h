#ifndef STMP_H
#define STMP_H

#include <QDebug>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>

//For Random number
#include <QtGlobal>
#include <QTime>

class Stmp : public QObject
{
    Q_OBJECT



    
public:
    explicit Stmp(QObject *parent = nullptr);
    void sendEmail(QString to, QString title, QString text);
    void sendVertifyCodeSlot(QString to);

    QString getVertifyCode();

    ~Stmp();
signals:
    void disconnected();
private:
    QSslSocket *sslSocket;

    ///已知
    QString serverIP;
    QString username;
    QString password;//pasword: pocikiajuoczfgoy
    QString conntoLewis;

    //////////
    QString to;
    QString title;
    QString text;
    QByteArray serverText;
    int status;
    QString VertifyCode;

public slots:
    void connectToServer();
    void disconnectFromServer();
    void getMessage();
};

#endif // STMP_H
