#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "test.h"
#include "doublemode.h"
#include "ai.h"
#include "setting.h"
namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    //void on_pushButton_clicked();

    void on_btn_sig_clicked();

    void on_btn_multi_clicked();

    void on_btn_AI_clicked();

    void on_btn_setting_clicked();

private:
    Ui::Window *ui;
    SnakeWindow clock;//钟表实例
    DoubleSnakeWindow doubl;
    AIWindow ai;
    Setting set;

};

#endif // WINDOW_H
