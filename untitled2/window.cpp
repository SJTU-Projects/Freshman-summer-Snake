#include "window.h"
#include "ui_window.h"
#include "test.h"
#include <QLabel>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::on_btn_sig_clicked()
{


        this->clock.restart();
        this->clock.show();



}

void Window::on_btn_multi_clicked()
{
this->doubl.show();
}

void Window::on_btn_AI_clicked()
{
    this->ai.restart();
    this->ai.show();
}

void Window::on_btn_setting_clicked()
{
    this->set.show();
}
