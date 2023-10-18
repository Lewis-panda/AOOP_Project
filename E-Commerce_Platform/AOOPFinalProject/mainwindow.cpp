#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
//for certification code
#include <QRegularExpression>
#include <QRegularExpressionValidator>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ShopClient =new Client();

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
        qDebug()<<"successful";
    else
        qDebug()<<"cannot open";





    ui->inputusername->setPlaceholderText("帳號");
    ui->lineEdit_2->setPlaceholderText("密碼");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setPlaceholderText("Email Address");
    ui->lineEdit_4->setPlaceholderText("密碼");
    ui->lineEdit_5->setPlaceholderText("確認密碼");
    ui->lineEdit_6->setPlaceholderText("Email Address");
    ui->lineEdit->setPlaceholderText("Account(username)");
    ui->searchLE->setPlaceholderText("輸入商品關鍵字 ...");
    //set linetext can input only "one" number 0~9
    QRegularExpressionValidator *v=new QRegularExpressionValidator(QRegularExpression("[0-9]"));
    ui->cheak1->setValidator(v);
    ui->cheak2->setValidator(v);
    ui->cheak3->setValidator(v);
    ui->cheak4->setValidator(v);
    ui->cheak5->setValidator(v);
    ui->cheak6->setValidator(v);
    ui->cheak1_4->setValidator(v);
    ui->cheak2_4->setValidator(v);
    ui->cheak3_4->setValidator(v);
    ui->cheak4_4->setValidator(v);
    ui->cheak5_4->setValidator(v);
    ui->cheak6_4->setValidator(v);

    initial = ui->stackedWidget->widget(0);
    register_1 = ui->stackedWidget->widget(1);
    register_2 = ui->stackedWidget->widget(2);
    forgetpassword = ui->stackedWidget->widget(3);
    home = ui->stackedWidget->widget(4);
    commodity = ui->stackedWidget->widget(5);
    seller = ui->stackedWidget->widget(6);
    register_add=ui->stackedWidget->widget(7);
    hitshelves=ui->stackedWidget->widget(8);
    cart = ui->stackedWidget->widget(9);
    order = ui->stackedWidget->widget(10);
    order_finished = ui->stackedWidget->widget(11);
    check_order = ui->stackedWidget->widget(12);
    cart2=ui->stackedWidget->widget(13);
    itemCheakout=ui->stackedWidget->widget(14);
    historypage=ui->stackedWidget->widget(15);
    chatroomlist=ui->stackedWidget->widget(16);
    chatroom=ui->stackedWidget->widget(17);

    ui->stackedWidget->setCurrentWidget(initial);

    connect(&manager[0], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad0(QNetworkReply*)));
    connect(&manager[1], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad1(QNetworkReply*)));
    connect(&manager[2], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad2(QNetworkReply*)));
    connect(&manager[3], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad3(QNetworkReply*)));
    connect(&manager[4], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad4(QNetworkReply*)));
    connect(&manager[5], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad5(QNetworkReply*)));
    connect(&manager[6], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoadCart(QNetworkReply*)));
    connect(&manager[7], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoadOrder(QNetworkReply*)));
    connect(&manager[8], SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoadCheckOrder(QNetworkReply*)));
    connect(&cartManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoadCart2(QNetworkReply*)));
    //enter commodity page
    connect(ui->label_37, SIGNAL(clicked()), this, SLOT(slotLabelClick0()));
    connect(ui->label_38, SIGNAL(clicked()), this, SLOT(slotLabelClick1()));
    connect(ui->label_39, SIGNAL(clicked()), this, SLOT(slotLabelClick2()));
    connect(ui->label_40, SIGNAL(clicked()), this, SLOT(slotLabelClick3()));
    connect(ui->label_41, SIGNAL(clicked()), this, SLOT(slotLabelClick4()));
    connect(ui->label_42, SIGNAL(clicked()), this, SLOT(slotLabelClick5()));
    connect(ui->label_78, SIGNAL(clicked()), this, SLOT(slotLabelClick78()));
    connect(ui->label_73, SIGNAL(clicked()), this, SLOT(display_cart2()));
    connect(ui->label_72, SIGNAL(clicked()), this, SLOT(display_cart2()));
    connect(ui->label_81, SIGNAL(clicked()), this, SLOT(slotLabelClick78()));
    connect(ui->label_102, SIGNAL(clicked()), this, SLOT(slotLabelClick78()));
    connect(ShopClient,SIGNAL(chatroommesg()), this, SLOT(chatnewmesg()));

    initial_picture();






}

MainWindow::~MainWindow()
{
    delete ui;
}

//need network!
void MainWindow::initial_picture()
{
    query = new QSqlQuery(database);
    query->exec("select Id, Product_name, Category, Selling_price, Weight, Quantity, Image,seller from goods");
    int randomValue = QRandomGenerator::global()->bounded(0, 100);
    for(int i=0;i<randomValue;i++)
        query->next();
    QNetworkRequest request;
    for(int i=0;i<6;i++)
    {
        item[i][0] = query->value(0).toString(); //store id
        item[i][1] = query->value(1).toString(); //store name
        item[i][2] = query->value(2).toString(); //store category
        item[i][3] = query->value(3).toString(); //store price
        item[i][4] = query->value(4).toString(); //store quantity
        item[i][5] = query->value(5).toString(); //store weight
        item[i][6] = query->value(7).toString(); //store seller
        QString Imageurl=query->value(6).toString();
        Imageurl.remove(QRegularExpression(" "));
        request.setUrl(QUrl(Imageurl)); //get http:/...
        manager[i].get(request);
        query->next();
    }




    ui->label_116->setText(item[0][1]);
    ui->label_118->setText(item[1][1]);
    ui->label_120->setText(item[2][1]);
    ui->label_122->setText(item[3][1]);
    ui->label_124->setText(item[4][1]);
    ui->label_126->setText(item[5][1]);

    ui->label_117->setText(item[0][3]);
    ui->label_119->setText(item[1][3]);
    ui->label_121->setText(item[2][3]);
    ui->label_123->setText(item[3][3]);
    ui->label_125->setText(item[4][3]);
    ui->label_127->setText(item[5][3]);



}


//剛輸入Email 要按註冊 need network!
void MainWindow::on_pushButton_5_clicked()
{
    //    ui->stackedWidget->setCurrentWidget(register_2);
    Stmp *smtp=new Stmp;
    connect(smtp, SIGNAL(disconnected()), smtp, SLOT(deleteLater()));

    //    QString receiver="lewis@lewisss.com";
    //    QString receiver="khjhs102109@gmail.com";
    //    QString receiver="jerry.ic.yu@gmail.com";

    QString receiver=ui->lineEdit_3->text(); //看user輸入啥

    //test for arbitrary content
    //    QString title="Hello!";
    //    QString content="Test";
    //    smtp->sendEmail(receiver, title, content);

    VertifyForDemo=smtp->getVertifyCode();
    //only for vertifycode
    smtp->sendVertifyCodeSlot(receiver);  //寄出

    ui->stackedWidget->setCurrentWidget(register_add);

    ui->cheak1_4->setFocus();


    UserRegister.Email=ui->lineEdit_3->text();
}

//Email認證已完成  註冊username    need network!
void MainWindow::on_pushButton_6_clicked()
{

    UserRegister.username=ui->lineEdit->text();
    if(ui->lineEdit_4->text()==ui->lineEdit_5->text())
    {
        UserRegister.password=ui->lineEdit_5->text();
        ui->label_65->setText("");
        ui->stackedWidget->setCurrentWidget(initial);

//        QSqlQuery *queryForRegister = new QSqlQuery(database);
//        query->exec("insert into goods values(11111,'PPPQQQ','None',100,0,0,0)");
        query->prepare("insert into userInfo values(:A,:B,:C)");
        query->bindValue(":A",UserRegister.username);
        query->bindValue(":B",UserRegister.password);
        query->bindValue(":C",UserRegister.Email);
        query->exec();//寫入

    }
    else
    {
        ui->label_65->setText("Error!");
        ui->label_65->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

//忘記! need network!
void MainWindow::on_pushButton_7_clicked()
{
    ui->pushButton_7->setText("驗證碼已送出");
    ui->resentcheakcode->setText("重新送出驗證碼");
    ui->pushButton_7->setStyleSheet("font: 700 10pt \"Microsoft JhengHei UI\";background-color: rgb(255, 206, 190);border-style:none");
    ui->cheak1->setFocus();

}


void MainWindow::on_cheak1_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak2->setFocus();
}

void MainWindow::on_cheak2_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak3->setFocus();
}

void MainWindow::on_cheak3_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak4->setFocus();
}

void MainWindow::on_cheak4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak5->setFocus();
}

void MainWindow::on_cheak5_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak6->setFocus();
}

//輸入完忘記密碼的驗證碼 //need network!
void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentWidget(initial);
}


//need network!  //登入按鈕
void MainWindow::on_pushButton_3_clicked()
{
    QString username=ui->inputusername->text();
    ShopClient->writeMesgToServer("Login/"+username); //寄出資訊給Server


    //右上角username
    ui->username->setText(username);
    ui->username_2->setText(username);
    ui->label_178->setText(username);
    ui->label_179->setText(username);


    CartUpdate(); //點購物車
    ui->label_31->setText(" " + QString::number(total_in_cart));
    ui->label_70->setText(" " + QString::number(total_in_cart));

   initial_picture();
    ui->stackedWidget->setCurrentWidget(home);


}


//need network!
void MainWindow::on_searchLE_editingFinished() //search commodity
{
    QNetworkRequest request;
    QString search = ui->searchLE->text(); //get what string customer enter
    query= new QSqlQuery(database);
    query->exec("select id, product_name, category, selling_price, quantity, weight, image,seller from goods");
    query->next();
    int counter = 0;

    while(query->next())
    {
        if( query->value(1).toString().indexOf(search) >= 0 || query->value(2).toString().indexOf(search) > 0) //successfully find match goods
        {
            item[counter][0] = query->value(0).toString(); //store id
            item[counter][1] = query->value(1).toString(); //store name
            item[counter][2] = query->value(2).toString(); //store category
            item[counter][3] = query->value(3).toString(); //store price
            item[counter][4] = query->value(4).toString(); //store quantity
            item[counter][5] = query->value(5).toString(); //store weight
            item[counter][6] = query->value(7).toString(); //store weight
            QString Imageurl=query->value(6).toString();
            Imageurl.remove(QRegularExpression(" "));
            request.setUrl(QUrl(Imageurl)); //get http:/...
            manager[counter].get(request);
            counter++;
            if(counter == 6)

                break;
        }
    }
    ui->label_47->setStyleSheet("");
//    qDebug()<<"search finished";

    ui->label_116->setText(item[0][1]);
    ui->label_118->setText(item[1][1]);
    ui->label_120->setText(item[2][1]);
    ui->label_122->setText(item[3][1]);
    ui->label_124->setText(item[4][1]);
    ui->label_126->setText(item[5][1]);

    ui->label_117->setText(item[0][3]);
    ui->label_119->setText(item[1][3]);
    ui->label_121->setText(item[2][3]);
    ui->label_123->setText(item[3][3]);
    ui->label_125->setText(item[4][3]);
    ui->label_127->setText(item[5][3]);
}



// display commodity information after clicking picture
void MainWindow::slotLabelClick0()
{
    ui->stackedWidget->setCurrentWidget(commodity);
    QPixmap pixmap;
    pixmap.loadFromData(bytes[0]);
    ConvertImageToTransparent(pixmap);
    if(!pixmap)
    {
        QString q="image: url(";
        q.append(item[0][5]);
        q.append(");");
        ui->label_47->setStyleSheet(q);
    }
    else
    {

        pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_47->setPixmap(pixmap);
    }


    ui->label_id->setText(item[0][0]);
    ui->label_53->setText(item[0][1]);
    ui->label_54->setText(item[0][2]);
    ui->label_55->setText(item[0][3]);
    ui->label_56->setText(item[0][4]);
    ui->label_57->setText(item[0][5]);
}

void MainWindow::slotLabelClick1()
{
    ui->stackedWidget->setCurrentWidget(commodity);
    QPixmap pixmap;
    pixmap.loadFromData(bytes[1]);
    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
//    pixmap.fill(Qt::transparent);//用透明色填充
    ui->label_47->setPixmap(pixmap);

    ui->label_id->setText(item[1][0]);
    ui->label_53->setText(item[1][1]);
    ui->label_54->setText(item[1][2]);
    ui->label_55->setText(item[1][3]);
    ui->label_56->setText(item[1][4]);
    ui->label_57->setText(item[1][5]);
    ui->label_138->setText(item[1][6]);
}

void MainWindow::slotLabelClick2()
{
    ui->stackedWidget->setCurrentWidget(commodity);
    QPixmap pixmap;
    pixmap.loadFromData(bytes[2]);
    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_47->setPixmap(pixmap);

    ui->label_id->setText(item[2][0]);
    ui->label_53->setText(item[2][1]);
    ui->label_54->setText(item[2][2]);
    ui->label_55->setText(item[2][3]);
    ui->label_56->setText(item[2][4]);
    ui->label_57->setText(item[2][5]);
    ui->label_138->setText(item[2][6]);
}

void MainWindow::slotLabelClick3()
{
    ui->stackedWidget->setCurrentWidget(commodity);
    QPixmap pixmap;
    pixmap.loadFromData(bytes[3]);
    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_47->setPixmap(pixmap);

    ui->label_id->setText(item[3][0]);
    ui->label_53->setText(item[3][1]);
    ui->label_54->setText(item[3][2]);
    ui->label_55->setText(item[3][3]);
    ui->label_56->setText(item[3][4]);
    ui->label_57->setText(item[3][5]);
    ui->label_138->setText(item[3][6]);
}

void MainWindow::slotLabelClick4()
{
    ui->stackedWidget->setCurrentWidget(commodity);
    QPixmap pixmap;
    pixmap.loadFromData(bytes[4]);
    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_47->setPixmap(pixmap);

    ui->label_id->setText(item[4][0]);
    ui->label_53->setText(item[4][1]);
    ui->label_54->setText(item[4][2]);
    ui->label_55->setText(item[4][3]);
    ui->label_56->setText(item[4][4]);
    ui->label_57->setText(item[4][5]);
    ui->label_138->setText(item[4][6]);
}

void MainWindow::slotLabelClick5()
{
    ui->stackedWidget->setCurrentWidget(commodity);
    QPixmap pixmap;
    pixmap.loadFromData(bytes[5]);
    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_47->setPixmap(pixmap);

    ui->label_id->setText(item[5][0]);
    ui->label_53->setText(item[5][1]);
    ui->label_54->setText(item[5][2]);
    ui->label_55->setText(item[5][3]);
    ui->label_56->setText(item[5][4]);
    ui->label_57->setText(item[5][5]);
    ui->label_138->setText(item[5][6]);
}

void MainWindow::slotLabelClick78()
{
    ui->stackedWidget->setCurrentWidget(home);
}

//display picture at home page
void MainWindow::slotReplyPixmapLoad0(QNetworkReply* reply)
{
    ui->label_37->setStyleSheet("");

    QString t= item[0][5];
//    qDebug()<<t;
    if(t.indexOf("C:/")>=0)
    {
//        qDebug()<<"~~";
        ui->label_37->setStyleSheet("");
        QString q="image: url(";
        q.append(t);
        q.append(");");
//        qDebug()<<q;
        ui->label_37->setStyleSheet(q);
    }

    bytes[0] = reply->readAll(); //store image info
    QPixmap pixmap;
    pixmap.loadFromData(bytes[0]);

    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_37->clear();
    ui->label_37->setPixmap(pixmap);
    reply->deleteLater();

}

void MainWindow::slotReplyPixmapLoad1(QNetworkReply* reply)
{
    bytes[1] = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(bytes[1]);

    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_38->setPixmap(pixmap);
    reply->deleteLater();
}

void MainWindow::slotReplyPixmapLoad2(QNetworkReply* reply)
{
    bytes[2] = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(bytes[2]);

    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_39->setPixmap(pixmap);
    reply->deleteLater();
}

void MainWindow::slotReplyPixmapLoad3(QNetworkReply* reply)
{
    bytes[3] = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(bytes[3]);

    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_40->setPixmap(pixmap);
    reply->deleteLater();
}

void MainWindow::slotReplyPixmapLoad4(QNetworkReply* reply)
{
    bytes[4] = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(bytes[4]);

    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_41->setPixmap(pixmap);
    reply->deleteLater();
}

void MainWindow::slotReplyPixmapLoad5(QNetworkReply* reply)
{
    bytes[5] = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(bytes[5]);

    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(pixmap);
    ui->label_42->setPixmap(pixmap);
    reply->deleteLater();
}

//need network!  輸入完驗證碼
void MainWindow::on_pushButton_37_clicked()
{
    //cheak vertify code!

    QString inputCode;
    inputCode.append(ui->cheak1_4->text());
    inputCode.append(ui->cheak2_4->text());
    inputCode.append(ui->cheak3_4->text());
    inputCode.append(ui->cheak4_4->text());
    inputCode.append(ui->cheak5_4->text());
    inputCode.append(ui->cheak6_4->text());
    qDebug()<<inputCode;
    qDebug()<<VertifyForDemo;

    if(inputCode==VertifyForDemo)
        ui->stackedWidget->setCurrentWidget(register_2);
    else
    {
        ui->pushButton_37->setStyleSheet("font: 700 10pt \"Microsoft JhengHei UI\";background-color: rgb(255, 206, 190);border-style:none");
        ui->label_58->setText("驗證碼錯誤!");
        ui->label_58->setStyleSheet("font: 700 10pt \"Microsoft JhengHei UI\";color: rgb(255,0,0)");
        ui->resentcheakcode_4->setText("重新送出驗證碼");
    }

    ui->cheak1_4->clear();
    ui->cheak2_4->clear();
    ui->cheak3_4->clear();
    ui->cheak4_4->clear();
    ui->cheak5_4->clear();
    ui->cheak6_4->clear();

}

void MainWindow::on_cheak1_4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak2_4->setFocus();
}

void MainWindow::on_cheak2_4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak3_4->setFocus();
}

void MainWindow::on_cheak3_4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak4_4->setFocus();
}

void MainWindow::on_cheak4_4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak5_4->setFocus();
}

void MainWindow::on_cheak5_4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->cheak6_4->setFocus();
}

void MainWindow::on_cheak6_4_textChanged(const QString &arg1)
{
    if(arg1!="")
        ui->pushButton_37->click();
}


//要上架商品按鈕
void MainWindow::on_pushButton_13_clicked()
{

    QString file_name = QFileDialog::getOpenFileName(NULL,"選擇圖片",".","*.*");
    QString setImage="image: url(";
    setImage.append(file_name);
    setImage.append(");");
//    QUrl a=QFileDialog::getOpenFileUrl(NULL,"*.*");
//    ui->label->setStyleSheet(setImage);
    setImage.append("border:hidden;");
    ui->pushButton_13->setText("");
    ui->pushButton_13->setStyleSheet(setImage);

//    qDebug()<<file_name;

    commodityForDemo.image=file_name;

}

//輸入完資訊 要上架商品Button needNetwork
void MainWindow::on_pushButton_15_clicked()
{

   commodityForDemo.id=42141;
   commodityForDemo.product_name=ui->lineEdit_7->text();
   commodityForDemo.category=ui->lineEdit_8->text();
   commodityForDemo.selling_price=ui->lineEdit_9->text();
   commodityForDemo.quantity=ui->lineEdit_10->text().toInt();
   commodityForDemo.weight=0;
   //商品介紹之後再補

   ui->stackedWidget->setCurrentWidget(seller);

   QSqlQuery qry(database);

   qry.prepare("insert into goods values(:A,:B,:C,:D,:E,:F,:G)");
   qry.bindValue(":A",commodityForDemo.id);
   qry.bindValue(":B",commodityForDemo.product_name);
   qry.bindValue(":C",commodityForDemo.category);
   qry.bindValue(":D",commodityForDemo.selling_price);
   qry.bindValue(":E",commodityForDemo.quantity);
   qry.bindValue(":F",commodityForDemo.weight);
   qry.bindValue(":G",commodityForDemo.image);
   qry.exec();//寫入


}

//進入 我的商店(查看上架的商品)
void MainWindow::on_pushButton_16_clicked()
{

}

//購物車中 按上一頁
void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
    ui->label_47->setStyleSheet("");
    ui->label_47->clear();
    ui->label_31->setText(" " + QString::number(total_in_cart));
}

//成立訂單後回首頁
void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}

/////
void MainWindow::slotReplyPixmapLoadCart(QNetworkReply* reply){}
void MainWindow::slotReplyPixmapLoadOrder(QNetworkReply* reply){}
void MainWindow::slotReplyPixmapLoadCheckOrder(QNetworkReply* reply){}
void MainWindow::on_pushButton_20_clicked(){}
void MainWindow::on_pushButton_21_clicked(){}
void MainWindow::on_pushButton_11_clicked(){}
void MainWindow::on_pushButton_18_clicked(){}
void MainWindow::display_order(){}
void MainWindow::wheelEvent ( QWheelEvent * event ){}
/////





//加入購物車 network!
void MainWindow::on_cart_buttom_clicked()
{
    QDir *folder = new QDir;
    folder->mkdir("incart");

    QSqlQuery qry(database);
    //if( qry.prepare("insert into cartInfo values(:username, :id :product_name, :category, :selling_pice, :quantity, :weight, :image)") )
    if( qry.prepare(" insert into cartInfo values(:username, :id) "))
    {
        qry.bindValue(":username",ui->username->text());
        qry.bindValue(":id",ui->label_id->text());
        if(qry.exec())//寫入
        {
            qDebug()<<"put in cart exec success";
            total_in_cart++;
            ui->label_70->setText(" " + QString::number(total_in_cart));
        }
    }

    imageid=ui->label_id->text();

    QString Imageurl;
    query= new QSqlQuery(database);
    query->exec("select Id, Image from goods");
    query->next();
    while(query->next())
        if( query->value(0) ==imageid ) //successfully find match product_id
            Imageurl=query->value(1).toString();//store image url

    QNetworkRequest request;
    Imageurl.remove(QRegularExpression(" "));
    request.setUrl(QUrl(Imageurl)); //get http:/...
    cartManager.get(request);
    //找圖片 命名為Imageid.png

    CartUpdate();
}

//更新購物車 network!
void MainWindow::CartUpdate()
{
    //在cartinfo中尋找    該username加入購物車的商品id 存在product_id<int>中
    QVector<int> product_id;
    QString username = ui->inputusername->text(); //get username
    query= new QSqlQuery(database);
    if( query->exec("select username, id from cartInfo") )
        qDebug()<<"select username, id from cartInfo successful";
    else
        qDebug()<<"select username, id from cartInfo failed";

    //找到該username購物車有的id存起來
    while(query->next())
        if( query->value(0).toString() == username )
            product_id.push_back(query->value(1).toInt());
    total_in_cart = product_id.length();

    //先對product_id排序 再從goods中搜尋
    sort(product_id.begin(),product_id.end());
    int index = 0;
    query->exec("select Id, Product_name, Category, Selling_price, Weight, Quantity, Image ,seller from goods");
    query->next();
    CartInfo.clear();
    while(query->next())
    {
        for(int i=0;i<product_id.length();i++)
        {
            if( query->value(0).toInt() == product_id[i] ) //successfully find match product_id
            {
                Cart tempC;
                tempC.content[0]=query->value(0).toString();//store id
                tempC.content[1]=query->value(1).toString();//store name
                tempC.content[2]=query->value(2).toString();//store category
                tempC.content[3]=query->value(3).toString().remove("$");//store price
                tempC.content[4]=query->value(4).toString();//store weight
                tempC.content[5]=query->value(5).toString();//store quantity
                tempC.content[6]=query->value(6).toString();//store image url
                tempC.content[7]="1";
                tempC.content[8]=query->value(7).toString(); //seller
                CartInfo.push_back(tempC);
                index++;
            }
        }
    }
//    qDebug()<<"cart_index search cart finished";
//    qDebug()<<"total number of product in cart: "<<total_in_cart<<CartInfo.size()<<index;
    ui->label_31->setText(" " + QString::number(total_in_cart));
    ui->label_70->setText(" " + QString::number(total_in_cart));
}

//存購物車中的圖片為id.png 當cartmaneger call.get()時
void MainWindow::slotReplyPixmapLoadCart2(QNetworkReply* reply)
{
    QPixmap P=QPixmap();
    QByteArray data_bytes = reply->readAll();
    P.loadFromData(data_bytes);
    P=P.scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ConvertImageToTransparent(P);

    QString PixmapName="./incart/";
    PixmapName+=imageid;
    PixmapName+=".png";
    P.save(PixmapName);

    reply->deleteLater();
}



//清空購物車 for debug! (network)
void MainWindow::on_pushButton_24_clicked()
{
    //在cartinfo中刪除username==username的
    QVector<int> product_id;
    QString username = ui->inputusername->text(); //get username
    query= new QSqlQuery(database);
    query->prepare("delete from cartInfo where username=(:A)");
    query->bindValue(":A",username);
    query->exec();
    total_in_cart=0;

    CartInfo.clear();
    ui->label_31->setText(" " + QString::number(total_in_cart));
    ui->label_70->setText(" " + QString::number(total_in_cart));

    //跳出選擇檔案框框
    //    QString str = QFileDialog::getOpenFileName(this,"選擇檔案","/","textfile(*.txt);;C file(*.cpp);;All file(*.*)");;
    //轉換檔案路徑
    //    QString get = str.toUtf8();
    //    //刪除檔案
    //    QFile::remove(get);

    //刪除資料夾(先不要，反正圖片不多)
    //    QDir dir;
    //    QString deletePath = QDir::currentPath() + "/incart/";
    //    dir.setPath(deletePath);
    //    dir.makeAbsolute();
    ////        qDebug()<<deletePath;
    //    if (dir.exists(deletePath))
    //        dir.removeRecursively();
}



//準備買單 ->還可以調整數量
void MainWindow::on_pushButton_27_clicked()
{

    spinboxlist.clear();
     priceLabelList.clear();
   //清空結帳畫面的layout和widget
   qDeleteAll(ui->scrollArea_3->widget()->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
   delete ui->scrollArea_3->widget()->layout();

   QGridLayout *pLayout = new QGridLayout();//網格Layout(會自動排版)
   pLayout->setColumnStretch(0,4);
   pLayout->setColumnStretch(1,16);
   pLayout->setColumnStretch(2,1);
   pLayout->setColumnStretch(3,1);
   if(CartInfo.size()==0)
   {
       QLabel *pLab= new QLabel(QString("Your don't choose any item!"), this);
       pLab->setStyleSheet("font: 700 20pt \"Microsoft JhengHei UI\";")  ;
       pLayout->addWidget(pLab,0,0);
   }



   double sum=0;
   for(int i=0;i<CartInfo.size();i++)
   {
       if(chosenitem[i]->isChecked())
       {
           pLayout->setRowMinimumHeight(i,100);

           QLabel *pLab1= new QLabel();   //image
           QLabel *pLab2= new QLabel(QString(CartInfo[i].content[1]), this);   //name
           QLabel *pLab3= new QLabel(QString(CartInfo[i].content[3]+" $"), this);  //price
           QSpinBox *pSpin= new QSpinBox();


           //存SpinBox
           pSpin->setMinimum(1);
           spinboxlist.push_back(pSpin);
           //存Label
           pLab3->setStyleSheet("font: 700 14pt \"Microsoft JhengHei UI\";");
           priceLabelList.push_back(pLab3);

           //處理圖片
           QString image="./incart/";
           image+=CartInfo[i].content[0];
           image+=".png";
           QPixmap pix(image);
           pix.scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
           pLab1->setPixmap(pix);

           pLayout->addWidget(pLab1,i,0);//     第i列0行
           pLayout->addWidget(pLab2,i,1);//     第i列0行
           pLayout->addWidget(pLab3,i,2);//     第i列0行
           pLayout->addWidget(pSpin,i,3);//     第i列0行

           sum+=CartInfo[i].content[3].toDouble();
       }
       for(int i =0; i<spinboxlist.size(); i++)
           QObject::connect(spinboxlist[i], SIGNAL(valueChanged(int)), this, SLOT(refreshitemcheakpage()));



   }
   ui->scrollArea_3->widget()->setLayout(pLayout);
   ui->label_133->setText("Total: "+QString::number(sum)+"$");

   ui->stackedWidget->setCurrentWidget(itemCheakout);
}

//當spinBox改變時 就call這個
void MainWindow::refreshitemcheakpage()
{
    double sum=0;
    int index=0;
    double itemprice;
    int amount;
    for(int i=0;i<CartInfo.size();i++)
    {
        if(chosenitem[i]->isChecked())
        {
            itemprice=CartInfo[i].content[3].toDouble();
            amount=spinboxlist[index]->value();
            CartInfo[i].content[7]=QString::number(amount);
            itemprice*=amount;
            priceLabelList[index]->setText(QString::number(itemprice)+"$");


            sum+=itemprice;
            index++;
        }

    }

    ui->label_133->setText("Total: "+QString::number(sum)+"$");
}


//從sql中讀歷史訂單 並存在program中 需要network
void MainWindow::on_pushButton_22_clicked()
{
    QVector<int> product_id;
    QString username = ui->inputusername->text();
    query= new QSqlQuery(database);
    if( query->exec("select username, id from historyInfo") )
        qDebug()<<"select username, id from historyInfo successful";
    else
        qDebug()<<"select username, id from historyInfo failed";

    while(query->next())
        if( query->value(0).toString() == username )
            product_id.push_back(query->value(1).toInt());


    sort(product_id.begin(),product_id.end());
    query->exec("select username,itemname, id, amount,seller,price from historyInfo");
    HistoryBuyItems.clear();
    while(query->next())
    {
        for(int i=0;i<product_id.length();i++)
        {
            if( query->value(2).toInt() == product_id[i] ) //successfully find match product_id
            {
                HistoryBuyItem tempH;
                tempH.id=query->value(2).toString();//store id
                tempH.amount=query->value(3).toString().toInt();//store amount
                tempH.price=query->value(5).toString().remove("$").toDouble();//store price
                tempH.username=query->value(0).toString();//store username
                tempH.itemname=query->value(1).toString();//store itemname
                tempH.seller=query->value(4).toString(); //seller
                HistoryBuyItems.push_back(tempH);
            }
        }
    }

    displayHistory();
}

//displayHistory不用network
void MainWindow::displayHistory()
{
    //清空History的layout和widget
    qDeleteAll(ui->scrollArea_4->widget()->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete ui->scrollArea_4->widget()->layout();

    QGridLayout *pLayout = new QGridLayout();//網格Layout(會自動排版)
    pLayout->setColumnStretch(0,2);
    pLayout->setColumnStretch(1,7);
    pLayout->setColumnStretch(2,1);
    pLayout->setColumnStretch(3,1);
    pLayout->setColumnStretch(4,1);
    if(HistoryBuyItems.size()==0)
    {
        QLabel *pLab= new QLabel(QString("Your historyOrders has not item!"), this);
        pLab->setStyleSheet("font: 700 20pt \"Microsoft JhengHei UI\";")  ;
        pLayout->addWidget(pLab,0,0);
    }

    for(int i=0;i<HistoryBuyItems.size();i++)
    {
        pLayout->setRowMinimumHeight(i,100);

        QLabel *pLab1= new QLabel();   //image
        QLabel *pLab2= new QLabel(QString(HistoryBuyItems[i].itemname), this);
        QLabel *pLab3= new QLabel(QString("$"+QString::number(HistoryBuyItems[i].price)), this);
        QLabel *pLab4= new QLabel(QString(QString::number(HistoryBuyItems[i].amount)), this);
        QLabel *pLab5= new QLabel(QString(HistoryBuyItems[i].seller), this);

        pLab2->setStyleSheet("font: 700 12pt \"Microsoft JhengHei UI\";")  ;
        pLab3->setStyleSheet("font: 700 13pt \"Microsoft JhengHei UI\";")  ;
        pLab4->setStyleSheet("font: 700 12pt \"Microsoft JhengHei UI\";")  ;
        pLab5->setStyleSheet("font: 700 12pt \"Microsoft JhengHei UI\";")  ;

        //處理圖片
        QString image="./incart/";
        image+=HistoryBuyItems[i].id;
        image+=".png";
        QPixmap pix(image);
        pix.scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        pLab1->setPixmap(pix);


        pLayout->addWidget(pLab1,i,0);//     第i列0行
        pLayout->addWidget(pLab2,i,1);//     第i列0行
        pLayout->addWidget(pLab3,i,2);//     第i列0行
        pLayout->addWidget(pLab4,i,3);//     第i列0行
        pLayout->addWidget(pLab5,i,4);//     第i列0行
    }
    ui->scrollArea_4->widget()->setLayout(pLayout);
    ui->stackedWidget->setCurrentWidget(historypage);
}
//display購物車 不需要network
void MainWindow::display_cart2()
{
    //清空購物車的layout和widget
    qDeleteAll(ui->scrollArea_2->widget()->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete ui->scrollArea_2->widget()->layout();

    QGridLayout *pLayout = new QGridLayout();//網格Layout(會自動排版)
    pLayout->setColumnStretch(0,2);
    pLayout->setColumnStretch(1,8);
    pLayout->setColumnStretch(2,1);
    pLayout->setColumnStretch(3,1);
    if(CartInfo.size()==0)
    {
        QLabel *pLab= new QLabel(QString("Your Cart has not item!"), this);
        pLab->setStyleSheet("font: 700 20pt \"Microsoft JhengHei UI\";")  ;
        pLayout->addWidget(pLab,0,0);
    }


    chosenitem.clear();
    for(int i=0;i<CartInfo.size();i++)
    {
        pLayout->setRowMinimumHeight(i,100);

        QLabel *pLab1= new QLabel();   //image
        QLabel *pLab2= new QLabel(QString(CartInfo[i].content[1]), this);   //name
        QLabel *pLab3= new QLabel(QString("$"+CartInfo[i].content[3]), this);  //price
        QCheckBox *pCheak=new QCheckBox;

        pLab3->setStyleSheet("font: 700 14pt \"Microsoft JhengHei UI\";")  ;
        pCheak->setCursor(Qt::PointingHandCursor);

        //處理圖片
        QString image="./incart/";
        image+=CartInfo[i].content[0];
        image+=".png";
        QPixmap pix(image);
        pix.scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        pLab1->setPixmap(pix);

        //存cheakBox
        chosenitem.push_back(pCheak);

        pLayout->addWidget(pLab1,i,0);//     第i列0行
        pLayout->addWidget(pLab2,i,1);//     第i列0行
        pLayout->addWidget(pLab3,i,2);//     第i列0行
        pLayout->addWidget(pCheak,i,3);//     第i列0行
    }
    ui->scrollArea_2->widget()->setLayout(pLayout);
    ui->stackedWidget->setCurrentWidget(cart2);
}


//下單(確認訂單)(寄信 network) 把資料傳回server
void MainWindow::on_pushButton_29_clicked()
{
    //有空的話：
   //建一個QList<訂單> Orders;
   //最後Orders.push_back(HistoryBuyItems);

   QSqlQuery qry(database);
   double sum=0;
   int index=0;
   double itemprice;
   int amount;
   for(int i=0;i<CartInfo.size();i++)
   {
       if(chosenitem[i]->isChecked())
       {

           itemprice=CartInfo[i].content[3].toDouble();
           amount=spinboxlist[index]->value();
           itemprice*=amount;
           sum+=itemprice;

           //把該商品加入確認下單(歷史購買)
           HistoryBuyItem SingleItem;
           SingleItem.id=CartInfo[i].content[0];
           SingleItem.itemname=CartInfo[i].content[1];
           SingleItem.price=itemprice;
           SingleItem.amount=amount;
//           HistoryBuyItems.push_back(SingleItem);

           if( qry.prepare(" insert into historyInfo values(:username,:itemname, :id, :amount,:seller,:price ) "))
           {
               qry.bindValue(":username",ui->username->text());
               qry.bindValue(":itemname",SingleItem.itemname);
               qry.bindValue(":id",SingleItem.id);
               qry.bindValue(":amount",SingleItem.amount);
               qry.bindValue(":seller",CartInfo[i].content[8]);
               qry.bindValue(":price",CartInfo[i].content[3].toDouble());


               if(qry.exec())//寫入
               {
                   qDebug()<<"put in history exec success";

               }
           }
           index++;//for traversal spinboxlist

           if( qry.prepare("delete from cartinfo where id=(:id);"))
           {
               qry.bindValue(":id",SingleItem.id);
               if(qry.exec())//寫入
               {
                   qDebug()<<"delete from cart exec success";
                   total_in_cart--;
               }
           }
       }
   }

   CartUpdate();
    ui->stackedWidget->setCurrentWidget(order_finished);

    //寄信通知購買結果!
    Stmp *smtp=new Stmp;
    connect(smtp, SIGNAL(disconnected()), smtp, SLOT(deleteLater()));

    QString receiver;
    query->exec("select username,email from userInfo");
    while(query->next())
    {
            if( query->value(0) == ui->username->text() ) //successfully find match product_id
            {
                receiver = query->value(1).toString();
            }
    }
    qDebug()<<receiver;



    int orderNumber;
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    orderNumber=rand()%100000;



    QString title;
    QString content;

    title="您的貨到付款訂單:#"+QString::number(orderNumber)+"已被確認";
    content="親愛的買家 ";
    content+=ui->username->text();
    content+="您好!\n\n";
    content.append("您的貨到付款訂單:#"+QString::number(orderNumber)+"已被確認\n");
    content.append("\n我們已通知賣家確認訂單後運送您的商品\n");
    content.append("\n請等待賣家出貨。\n");
    content.append("\n收到商品確認無誤後，請透過ShopooA完成訂單\n");
    content.append("\n\nFrom : ShopooA\n");
    content.append("\n-----------------------------------------------\n");
    content.append("\nAny Question?\n");
    content.append("\nPhone : 0966006717\n");
    content.append("\nEmail : lewis@lewisss.com\n");
    content.append("\nContact us whenever you want.\n");
    content.append("\n-----------------------------------------------\n");
    smtp->sendEmail(receiver, title, content);

}



//切換頁面的button
void MainWindow::on_toRegisterButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(register_1);
}
void MainWindow::on_pushButton_30_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}
void MainWindow::on_pushButton_31_clicked()
{
     ui->stackedWidget->setCurrentWidget(home);
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(forgetpassword);\
}
void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(seller);
}
void MainWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}
void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(initial);
}
void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(hitshelves);
}
void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}
void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}
void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}
////


//網路測試
void MainWindow::on_pushButton_32_clicked()
{
    ShopClient->writeMesgToServer("Hello Server I'm Lewis");
}


void MainWindow::on_pushButton_33_clicked()
{
//    qDebug()<<ShopClient->getmesg();
}

//圖片去背景
void MainWindow::ConvertImageToTransparent(QPixmap &qPixmap)
{
    QImage image = qPixmap.toImage();
    image = image.convertToFormat(QImage::Format_ARGB32);
    union myrgb
    {
        uint rgba;
        uchar rgba_bits[4];
    };
    myrgb* mybits =(myrgb*) image.bits();
    int len = image.width()*image.height();
    while(len > 0)
    {
        len--;
        mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:255;
        mybits++;
    }

    qPixmap=QPixmap::fromImage(image);
}

//密碼隱藏or開啟
void MainWindow::on_pushButton_4_clicked()
{
    seePassword++;
    if(seePassword%2==1)
    {
        ui->pushButton_4->setStyleSheet("border:hidden;qproperty-icon:url(:/images/Y.png);");
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->pushButton_4->setStyleSheet("border:hidden;qproperty-icon:url(:/images/N.png);");
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

//已經有帳號，點此登入
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(initial);
}


void MainWindow::on_pushButton_5_pressed()
{
    ui->pushButton_5->setStyleSheet("font: 700 10pt \"Microsoft JhengHei UI\";background-color: rgb(255, 206, 190);border-style:none");
}
void MainWindow::on_pushButton_5_released()
{
    ui->pushButton_5->setStyleSheet("font: 700 10pt \"Microsoft JhengHei UI\";background-color: rgb(225, 206, 190);border-style:none");
}

void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}


void MainWindow::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}


//To chat Room list
void MainWindow::on_pushButton_34_clicked()
{
    ui->stackedWidget->setCurrentWidget(chatroomlist);
}



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->stackedWidget->setCurrentWidget(chatroom);
    sendto=item->text();
    ui->label_177->setText("Char Room with "+sendto);
}


void MainWindow::on_pushButton_39_clicked()
{
    ui->stackedWidget->setCurrentWidget(home);
}


void MainWindow::on_pushButton_38_clicked()
{
    QString message=ui->lineEdit_11->text();
    ui->lineEdit_11->clear();

    QString from=ui->username->text();

    QString M="Message/"+from+'/'+sendto+'/'+message;
    ShopClient->writeMesgToServer(M);



    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();
    int minute = current_time.minute();
    int second = current_time.second();
    QString currentTime='['+QString::number(hour)+':'+QString::number(minute)+':'+QString::number(second)+"] ";

    ui->textBrowser->append(currentTime+"You say: ");
    ui->textBrowser->setAlignment(Qt::AlignRight);
    ui->textBrowser->append(message);
    ui->textBrowser->setAlignment(Qt::AlignRight);

}

void MainWindow::chatnewmesg()
{
    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();
    int minute = current_time.minute();
    int second = current_time.second();
    QString currentTime='['+QString::number(hour)+':'+QString::number(minute)+':'+QString::number(second)+"] ";
    ui->textBrowser->append(currentTime);
    ui->textBrowser->setAlignment(Qt::AlignLeft);
    ui->textBrowser->append(ShopClient->getmesg());
    ui->textBrowser->setAlignment(Qt::AlignLeft);

}
