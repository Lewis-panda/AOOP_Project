#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QSqlResult>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QApplication>
#include <QWheelEvent>

#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include<QDir>
#include <QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int count;
    unsigned short port;
    QTcpServer *server;
    //multi-client server
    QList<QTcpSocket*> sockets;
    QList<QString> socketname;
    int index;
    QString SeMesg;
    int sendto;


    QSqlDatabase database;
    QSqlQuery *query;
private slots:
    void slotNewConnection();
    void slotReadyRead();
    void slotDisconnected();

};
#endif // MAINWINDOW_H
