#include "setting.h"
#include "ui_setting.h"
#include <QMediaPlayer>

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}


void Setting::on_btn_m1_clicked()
{
     static QMediaPlayer *player1 = new QMediaPlayer;
    if(this->ui->btn_m1->text()=="神の怒り")
    {

        player1->setMedia(QUrl::fromLocalFile("D:/C++++++++++++++++++++/QTlerning/Workplace/untitled2/光宗信吉 - 神の怒り (神之怒).mp3"));
        player1->setVolume(50);
        player1->play();
        this->ui->btn_m1->setText("再次点击以停止");
    }
    else{
            player1->stop();
            delete player1;
            this->ui->btn_m1->setText("神の怒り");
    }
        //"E:\\CloudMusic\\林沁简介 - 太阳的后裔 MIX.mp3""D:/C++++++++++++++++++++/QTlerning/Workplace/untitled2/光宗信吉 - 神の怒り (神之怒).mp3"
    /*Phonon::MediaObject *music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("/home/myprogram/qt/QTFaceRec-build-desktop/test.wav"));
    music->play();*/
}

void Setting::on_btn_m2_clicked()
{
    static QMediaPlayer *player2 = new QMediaPlayer;
   if(this->ui->btn_m2->text()=="高潔なる教皇")
   {

       player2->setMedia(QUrl::fromLocalFile("D:/C++++++++++++++++++++/QTlerning/Workplace/untitled2/菅野祐悟 - 高潔なる教皇 (高洁的教皇).mp3"));
       player2->setVolume(50);
       player2->play();
       this->ui->btn_m2->setText("再次点击以停止");
   }
   else{
           player2->stop();
           delete player2;
           this->ui->btn_m2->setText("高潔なる教皇");
   }
}

void Setting::on_btn_m3_clicked()
{
    static QMediaPlayer *player3 = new QMediaPlayer;
   if(this->ui->btn_m3->text()=="遊星バトル")
   {

       player3->setMedia(QUrl::fromLocalFile("D:/C++++++++++++++++++++/QTlerning/Workplace/untitled2/Wall5 Project - 遊星バトル (游星战斗).mp3"));
       player3->setVolume(50);
       player3->play();
       this->ui->btn_m3->setText("再次点击以停止");
   }
   else{
           player3->stop();
           delete player3;
           this->ui->btn_m3->setText("遊星バトル");
   }
}
