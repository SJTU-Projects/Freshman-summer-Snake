#ifndef SETTING_H
#define SETTING_H

#include <QMediaPlayer>
#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    //QMediaPlayer *player;

private slots:
    void on_btn_m1_clicked();

    void on_btn_m2_clicked();

    void on_btn_m3_clicked();

private:
    Ui::Setting *ui;
    //QMediaPlayer * player;
    //QMediaPlayer *player = new QMediaPlayer;
};

#endif // SETTING_H
