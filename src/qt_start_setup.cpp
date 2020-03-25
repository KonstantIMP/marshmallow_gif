#include "../include/qt_start_setup.hpp"
#include "../form/ui_qt_start_setup.h"

#include <QIcon>

#include <QDebug>

qt_start_setup::qt_start_setup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qt_start_setup)
{
    ui->setupUi(this);

    this->setWindowTitle("Let`s go");
    this->setWindowIcon(QIcon("image/start.png"));

    get_lang();
}

qt_start_setup::~qt_start_setup()
{
    delete ui;
}

void qt_start_setup::get_lang()
{
    if(QLocale::system().name() == "ru_RU"){
        ui->hello_msg->setText("Привет!");
        ui->thank_msg->setText("Спасибо за выбор нашего програмного обеспечения!\nПриятного использования!");

        ui->lang_btn->setIcon(QIcon("image/en.png"));
        ui->lang_btn->setText("EN");

        ui->theme_msg->setText("Выберите оформление");

        ui->system_msg->setText("Системный");
        ui->system_btn->setText("Как обычно");

        ui->marsh_msg->setText("Зефирный");
        ui->marsh_btn->setText("Фирменный");

        ui->or_msg->setText("Оранжевый");
        ui->or_btn->setText("Мандарины");
    }
    else{

    }
}
