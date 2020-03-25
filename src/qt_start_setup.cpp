#include "../include/qt_start_setup.hpp"
#include "../form/ui_qt_start_setup.h"

#include "../include/config.hpp"

#include <QCloseEvent>
#include <QPushButton>
#include <QIcon>

#include <QMessageBox>

QString theme;

qt_start_setup::qt_start_setup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qt_start_setup)
{
    ui->setupUi(this);

    this->setWindowTitle("Let`s go");

    this->setWindowIcon(QIcon("image/start.png"));

    if(QLocale::system().name() == "ru_RU") {
        set_ru();
        QMessageBox::warning(this, "Внимание", "По умолчанию используется интерфейс на QT.\nВы можете изхменить это в настройках\n(Не рекомендуется на Win и MacOS)");
    }
    else {
        set_en();
        QMessageBox::warning(this, "Warning", "The default interface is on QT.\nYou can change this in the settings\n(Not recommended on Win and MacOS)");
    }

    set_sys();

    connect(ui->lang_btn, &QPushButton::clicked, this, &qt_start_setup::change_lang);

    connect(ui->system_btn, &QPushButton::clicked, this, &qt_start_setup::set_sys);
    connect(ui->marsh_btn, &QPushButton::clicked, this, &qt_start_setup::set_marsh);
    connect(ui->or_btn, &QPushButton::clicked, this, &qt_start_setup::set_or);

    connect(ui->ok_btn, &QPushButton::clicked, this, &qt_start_setup::close);
}

qt_start_setup::~qt_start_setup()
{
    delete ui;
}

void qt_start_setup::change_lang()
{
    if(ui->lang_btn->text() == "EN") set_en();
    else set_ru();
}

void qt_start_setup::set_sys()
{
    theme = "system";

    this->setStyleSheet("");

    ui->hello_msg->setStyleSheet("QLabel{"
                                 "font-size: 32px;"
                                 "font-family: \"Arial\", \"Times New Roman\";"
                                 "margin-bottom: 3px;"
                                 "}");

    ui->thank_msg->setStyleSheet("QLabel{"
                                 "font-size: 14px;"
                                 "font-family: \"Arial\", \"Times New Roman\";"
                                 "margin-top: 3px;"
                                 "}");

    ui->line->setStyleSheet("");

    ui->lang_btn->setStyleSheet("QPushButton{"
                                "font-size:23px;"
                                "}");

    ui->line_2->setStyleSheet("");

    ui->theme_msg->setStyleSheet("QLabel{"
                                 "font-size: 18px;"
                                 "font-family: \"Arial\", \"Times New Roman\";"
                                 "}");

    ui->system_msg->setStyleSheet("QLabel{"
                                  "font-size: 12px;"
                                  "font-family: \"Arial\", \"Times New Roman\";"
                                  "}");

    ui->marsh_msg->setStyleSheet("QLabel{"
                                  "font-size: 12px;"
                                  "font-family: \"Arial\", \"Times New Roman\";"
                                  "}");

    ui->or_msg->setStyleSheet("QLabel{"
                                  "font-size: 12px;"
                                  "font-family: \"Arial\", \"Times New Roman\";"
                                  "}");
}

void qt_start_setup::set_marsh()
{
    theme = "marshmallow";

    this->setStyleSheet("background-color:#2d313d;");

    ui->hello_msg->setStyleSheet("QLabel{"
                                 "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                 "font-size: 32px;"
                                 "color: #ffffff;"
                                 "}");

    ui->thank_msg->setStyleSheet("QLabel{"
                                 "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                 "font-size: 14px;"
                                 "color: #ffffff;"
                                 "}");

    ui->line->setStyleSheet("border: 2px solid #e8324f;");

    ui->lang_btn->setStyleSheet("QPushButton{"
                                "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                "font-size: 14px;"
                                "background-color: #2d313d;"
                                "color: #ffffff;"
                                "border-radius: 8px;"
                                "border: 2px solid #e8324f;"
                                "}"
                                "QPushButton:hover{"
                                "background-color: #ffffff;"
                                "color: #2d313d;"
                                "}"
                                "QPushButton:pressed{"
                                "background-color: #ffffff;"
                                "color: #e8324f;"
                                "border-color: #ffffff;"
                                "}");

    ui->line_2->setStyleSheet("border: 2px solid #e8324f;");

    ui->theme_msg->setStyleSheet("QLabel{"
                                 "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                 "font-size: 15px;"
                                 "color: #ffffff;"
                                 "margin-bottom: 10px;"
                                 "}");

    ui->system_msg->setStyleSheet("QLabel{"
                                  "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                  "font-size: 12px;"
                                  "color: #ffffff;"
                                  "}");

    ui->marsh_msg->setStyleSheet("QLabel{"
                                  "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                  "font-size: 12px;"
                                  "color: #ffffff;"
                                  "}");

    ui->or_msg->setStyleSheet("QLabel{"
                                  "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                  "font-size: 12px;"
                                  "color: #ffffff;"
                                  "}");

    ui->ok_btn->setStyleSheet("QPushButton{"
                                "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                "font-size: 14px;"
                                "background-color: #2d313d;"
                                "color: #ffffff;"
                                "border-radius: 8px;"
                                "border: 2px solid #e8324f;"
                                "}"
                                "QPushButton:hover{"
                                "background-color: #ffffff;"
                                "color: #2d313d;"
                                "}"
                                "QPushButton:pressed{"
                                "background-color: #ffffff;"
                                "color: #e8324f;"
                                "border-color: #ffffff;"
                                "}");
}

void qt_start_setup::set_or()
{
    theme = "oranje";

    this->setStyleSheet("background-color: #363636;");

    ui->hello_msg->setStyleSheet("QLabel{"
                                 "font-family: \"DejaVu Sans\", \"Georgia\";"
                                 "font-size: 32px;"
                                 "color: #ffffff;"
                                 "}");

    ui->thank_msg->setStyleSheet("QLabel{"
                                 "font-family: \"DejaVu Sans\", \"Georgia\";"
                                 "font-size: 14px;"
                                 "color: #ffffff;"
                                 "}");

    ui->line->setStyleSheet("border: 1px solid #dd4d00;");

    ui->lang_btn->setStyleSheet("QPushButton{"
                                "font-family: \"DejaVu Sans\", \"Georgia\";"
                                "font-size: 14px;"
                                "background-color: #363636;"
                                "color: #ffffff;"
                                "border-radius: 0px;"
                                "border: 2px solid #ff4d00;"
                                "}"
                                "QPushButton:hover{"
                                "background-color: #ff4d00;"
                                "border-color: #363636;"
                                "}"
                                "QPushButton:pressed{"
                                "background-color: #ffffff;"
                                "color: #ff4d00;"
                                "border-color: #363636;"
                                "}");

    ui->line_2->setStyleSheet("border: 2px solid #dd4d00;");

    ui->system_msg->setStyleSheet("QLabel{"
                                  "font-family: \"DejaVu Sans\", \"Georgia\";"
                                  "font-size: 12px;"
                                  "color: #ffffff;"
                                  "}");

    ui->marsh_msg->setStyleSheet("QLabel{"
                                  "font-family: \"DejaVu Sans\", \"Georgia\";"
                                  "font-size: 12px;"
                                  "color: #ffffff;"
                                  "}");

    ui->or_msg->setStyleSheet("QLabel{"
                                  "font-family: \"DejaVu Sans\", \"Georgia\";"
                                  "font-size: 12px;"
                                  "color: #ffffff;"
                                  "}");

    ui->ok_btn->setStyleSheet("QPushButton{"
                                "font-family: \"DejaVu Sans\", \"Georgia\";"
                                "font-size: 14px;"
                                "background-color: #363636;"
                                "color: #ffffff;"
                                "border-radius: 0px;"
                                "border: 2px solid #ff4d00;"
                                "}"
                                "QPushButton:hover{"
                                "background-color: #ff4d00;"
                                "border-color: #363636;"
                                "}"
                                "QPushButton:pressed{"
                                "background-color: #ffffff;"
                                "color: #ff4d00;"
                                "border-color: #363636;"
                                "}");
}

void qt_start_setup::set_ru()
{
    ui->hello_msg->setText("Привет!");
    ui->thank_msg->setText("Спасибо за выбор нашего програмного обеспечения!\nПриятного использования!");

    ui->lang_btn->setIcon(QIcon("image/en.png"));
    ui->lang_btn->setIconSize(QSize(40,40));
    ui->lang_btn->setText("EN");

    ui->theme_msg->setText("Выберите оформление");

    ui->system_msg->setText("Системный");
    ui->system_btn->setText("Как обычно");

    ui->marsh_msg->setText("Зефирный");
    ui->marsh_btn->setText("Фирменный");

    ui->or_msg->setText("Оранжевый");
    ui->or_btn->setText("Мандарины");
}

void qt_start_setup::set_en()
{
    ui->hello_msg->setText("Hello!");
    ui->thank_msg->setText("Thanks for using this programm!\nEnjoy using!");

    ui->lang_btn->setIcon(QIcon("image/ru.png"));
    ui->lang_btn->setIconSize(QSize(40,40));
    ui->lang_btn->setText("РУ");

    ui->theme_msg->setText("Choose style");

    ui->system_msg->setText("System");
    ui->system_btn->setText("Classic");

    ui->marsh_msg->setText("Marshmallow");
    ui->marsh_btn->setText("Branded");

    ui->or_msg->setText("Oranje");
    ui->or_btn->setText("Oranjes");
}

void qt_start_setup::closeEvent(QCloseEvent *event)
{
    if(ui->lang_btn->text() == "EN") create_cfg("qt", theme.toStdString(), "ru", STANDART, STANDART, STANDART, STANDART);
    else create_cfg("qt", theme.toStdString(), "en", STANDART, STANDART, STANDART, STANDART);

    event->accept();
}
