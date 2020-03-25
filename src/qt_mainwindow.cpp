#include "../include/qt_mainwindow.hpp"
#include "../form/ui_qt_mainwindow.h"

#include "../include/config.hpp"

#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("marshmallow_gif");
    this->setWindowIcon(QIcon("image/candy.png"));

    if(get_param(LANG) == "ru") {
        ui->open_btn->setText("Открыть");
        ui->speed_msg->setText("Скорость :");
    }
    else {
        ui->open_btn->setText("Open");
        ui->speed_msg->setText("Speed :");
    }

    ui->indicator_msg->setText("100 %");

    if(get_param(THEME) == "marshmallow") set_marsh();
    else if(get_param(THEME) == "oranje") set_or();
    else set_sys();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_sys()
{

}

void MainWindow::set_marsh()
{
    this->setStyleSheet("background-color: #2d313d;");

    ui->gif_place->setStyleSheet("QLabel{"
                                 "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                 "font-size: 32px;"
                                 "color: #ffffff;"
                                 "background-color: #2d313d;"
                                 "border-radius: 5px;"
                                 "border: 2px solid #e8324f;"
                                 "padding: 0px;"
                                 "}");

    ui->exit_btn->setIcon(QIcon("image/m_exit.png"));
    ui->exit_btn->setIconSize(QSize(28, 28));
    ui->exit_btn->setStyleSheet("QPushButton{"
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

    ui->option_btn->setIcon(QIcon("image/m_settings.png"));
    ui->option_btn->setIconSize(QSize(28, 28));
    ui->option_btn->setStyleSheet("QPushButton{"
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
    ui->open_btn->setStyleSheet("QPushButton{"
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

    ui->pp_btn->setIcon(QIcon("image/m_play.png"));
    ui->pp_btn->setIconSize(QSize(28, 28));
    ui->pp_btn->setStyleSheet("QPushButton{"
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

    ui->speed_msg->setStyleSheet("QLabel{"
                                 "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                 "font-size: 16px;"
                                 "color: #ffffff;"
                                 "border-top: 2px solid #e8324f;"
                                 "border-left: 2px solid #e8324f;"
                                 "border-top-left-radius: 7px;"
                                 "padding-left: 4px;"
                                 "}");

    ui->prev_frame_btn->setIcon(QIcon("image/m_prev_frame.png"));
    ui->prev_frame_btn->setIconSize(QSize(28, 28));
    ui->prev_frame_btn->setStyleSheet("QPushButton{"
                                      "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                      "font-size: 14px;"
                                      "background-color: #2d313d;"
                                      "color: #ffffff;"
                                      "border-radius: 0px;"
                                      "border-top: 2px solid #e8324f;"
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

    ui->next_frame_btn->setIcon(QIcon("image/m_next_frame.png"));
    ui->next_frame_btn->setIconSize(QSize(28, 28));
    ui->next_frame_btn->setStyleSheet("QPushButton{"
                                      "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                      "font-size: 14px;"
                                      "background-color: #2d313d;"
                                      "color: #ffffff;"
                                      "border-top-right-radius: 8px;"
                                      "border-top: 2px solid #e8324f;"
                                      "border-right: 2px solid #e8324f;"
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

    ui->indicator_msg->setStyleSheet("QLabel{"
                                     "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                     "font-size: 16px;"
                                     "color: #ffffff;"
                                     "border-bottom: 2px solid #e8324f;"
                                     "border-left: 2px solid #e8324f;"
                                     "border-bottom-left-radius: 7px;"
                                     "padding-right: 4px;"
                                     "}");

    ui->speed_minus->setIcon((QIcon("image/m_minus.png")));
    ui->speed_minus->setIconSize(QSize(28, 28));
    ui->speed_minus->setStyleSheet("QPushButton{"
                                   "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                   "font-size: 14px;"
                                   "background-color: #2d313d;"
                                   "color: #ffffff;"
                                   "border-radius: 0px;"
                                   "border-bottom: 2px solid #e8324f;"
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

    ui->speed_plus->setIcon((QIcon("image/m_plus.png")));
    ui->speed_plus->setIconSize(QSize(28, 28));
    ui->speed_plus->setStyleSheet("QPushButton{"
                                   "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                   "font-size: 14px;"
                                   "background-color: #2d313d;"
                                   "color: #ffffff;"
                                   "border-radius: 0px;"
                                   "border-bottom: 2px solid #e8324f;"
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

    ui->speed_re->setIcon(QIcon("image/m_reset.png"));
    ui->speed_re->setIconSize(QSize(28, 28));
    ui->speed_re->setStyleSheet("QPushButton{"
                                "font-family: \"Comic Sans MS\", \"Arial\", \"Hack\";"
                                "font-size: 14px;"
                                "background-color: #2d313d;"
                                "color: #ffffff;"
                                "border-bottom-right-radius: 7px;"
                                "border-bottom: 2px solid #e8324f;"
                                "border-right: 2px solid #e8324f;"
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

void MainWindow::set_or()
{

}
