#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <windows.h>
#include <QMainWindow>
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
#include <clickablelabel.h>
#include "stmp.h"
#include "client.h"
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_toRegisterButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    void on_pushButton_5_pressed();
    void on_pushButton_5_released();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_2_clicked();
    // for certification code , (When input a number) auto jump to next
    void on_cheak1_textChanged(const QString &arg1);
    void on_cheak2_textChanged(const QString &arg1);
    void on_cheak3_textChanged(const QString &arg1);
    void on_cheak4_textChanged(const QString &arg1);
    void on_cheak5_textChanged(const QString &arg1);


    void on_pushButton_8_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_10_clicked();

    void on_searchLE_editingFinished();
    void slotReplyPixmapLoad0(QNetworkReply* reply);
    void slotReplyPixmapLoad1(QNetworkReply* reply);
    void slotReplyPixmapLoad2(QNetworkReply* reply);
    void slotReplyPixmapLoad3(QNetworkReply* reply);
    void slotReplyPixmapLoad4(QNetworkReply* reply);
    void slotReplyPixmapLoad5(QNetworkReply* reply);
    void slotReplyPixmapLoadCart(QNetworkReply* reply);
    void slotReplyPixmapLoadOrder(QNetworkReply* reply);
    void slotReplyPixmapLoadCheckOrder(QNetworkReply* reply);
    void slotReplyPixmapLoadCart2(QNetworkReply* reply);
    void slotLabelClick0();
    void slotLabelClick1();
    void slotLabelClick2();
    void slotLabelClick3();
    void slotLabelClick4();
    void slotLabelClick5();
    void slotLabelClick78();

    void on_pushButton_37_clicked();
    void on_cheak1_4_textChanged(const QString &arg1);
    void on_cheak2_4_textChanged(const QString &arg1);
    void on_cheak3_4_textChanged(const QString &arg1);
    void on_cheak4_4_textChanged(const QString &arg1);
    void on_cheak5_4_textChanged(const QString &arg1);

    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();

    void on_cheak6_4_textChanged(const QString &arg1);
    void on_pushButton_17_clicked();
    void on_cart_buttom_clicked();
    void wheelEvent ( QWheelEvent *) override;
    void on_pushButton_11_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();

    void on_pushButton_24_clicked();
    void display_cart2();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void refreshitemcheakpage();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_35_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_39_clicked();

    void on_pushButton_38_clicked();
    void chatnewmesg();

private:
    int current_index;
    int current_index_order;
    int total_in_cart;
    int total_order;
    Ui::MainWindow *ui;
    int seePassword=0; //for login
    QWidget *initial;
    QWidget *register_1;
    QWidget *register_2;
    QWidget *forgetpassword;
    QWidget *home;
    QWidget *seller;
    QWidget *commodity;
    QWidget *register_add;
    QWidget *hitshelves;
    QWidget *cart;
    QWidget *order;
    QWidget *order_finished;
    QWidget *check_order;
    QWidget *cart2;
    QWidget *itemCheakout;
    QWidget *historypage;
    QWidget *chatroomlist;
    QWidget *chatroom;


    QSqlDatabase database;
    QSqlQuery *query;
    QString item[6][7]; //store info of id, commodity name, category, price, quantity, weight
    QString carts[30][9];
    QString orders[30][9];
    QByteArray bytes[9]; //store info of image
    QNetworkAccessManager manager[9],cartManager;
    QString VertifyForDemo;
    void initial_picture();
    void display_order();
    void CartUpdate();
    void ConvertImageToTransparent(QPixmap &);
    void displayHistory();

    struct newRegister
    {
        QString username;
        QString password;
        QString Email;
    } UserRegister;






    struct HistoryBuyItem
    {
        QString id;
        QString username;
        QString itemname;
        double price;
        int amount;
        QString seller;
    } ;
    QVector<HistoryBuyItem> HistoryBuyItems;


    //for Demo2
    struct commodity
    {
        int id;
        QString product_name;
        QString category;
        QString selling_price;
        int quantity;
        QString weight=0;
        QString image;
    } commodityForDemo;


    struct Cart
    {
        QString content[9];
    } ;
    QVector<Cart> CartInfo;

    int pixmapNo;
    QString imageid;
    QList<QCheckBox*> chosenitem;
    QList<QSpinBox*> spinboxlist;
    QList<QLabel*>  priceLabelList;

    Client* ShopClient;


    QString sendto;
    QString newmesg;
};
#endif // MAINWINDOW_H
