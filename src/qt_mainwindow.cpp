#include "../include/qt_mainwindow.hpp"
#include "../form/ui_qt_mainwindow.h"

#include "../include/config.hpp"

#include <QFileDialog>
#include <QIcon>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pp_status = false;
    speed = 100;

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

    gif_animation = NULL;

    connect(ui->exit_btn, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->open_btn, &QPushButton::clicked, this, &MainWindow::open_gif);
    connect(ui->speed_plus, &QPushButton::clicked, this, &MainWindow::speed_plus);
    connect(ui->speed_minus, &QPushButton::clicked, this, &MainWindow::speed_minus);
    connect(ui->speed_re, &QPushButton::clicked, this, &MainWindow::speed_reset);
    connect(ui->next_frame_btn, &QPushButton::clicked, this, &MainWindow::frame_plus);
    connect(ui->prev_frame_btn, &QPushButton::clicked, this, &MainWindow::frame_minus);
    connect(ui->pp_btn, &QPushButton::clicked, this, &MainWindow::change_pp_status);
}

MainWindow::~MainWindow()
{
    delete gif_animation;
    delete ui;
}

void MainWindow::load_from_file(std::string file_name)
{
    if(file_name == "" || file_name.substr(file_name.length() - 3, 3) != "gif") return;

    if(gif_animation != NULL) delete gif_animation;

    gif_animation = new QMovie;

    gif_animation->setFileName(file_name.c_str());

    ui->gif_place->clear();
    ui->gif_place->setMovie(gif_animation);

    gif_animation->start();

    ui->indicator_msg->setText("100 %");

    speed = 100;
    pp_status = true;

    pp_btn_change();
}

void MainWindow::open_gif()
{
    load_from_file(QFileDialog::getOpenFileName(this, "Choose gif", QString(), "*.gif").toStdString());
}

void MainWindow::change_pp_status()
{
    if(gif_animation == NULL) return;

    if(pp_status == false) gif_animation->start();
    else {
        gif_animation->stop();
    }

    pp_status = !pp_status;

    pp_btn_change();
}

void MainWindow::speed_plus()
{
    if(gif_animation == NULL) return;

    if(speed < 1000) speed += 5;
    else speed = 5;

    gif_animation->setSpeed(speed);

    ui->indicator_msg->setText(QString::number(speed) + " %");
}

void MainWindow::speed_minus()
{
    if(gif_animation == NULL) return;

    if(speed > 5) speed -= 5;
    else speed = 1000;

    gif_animation->setSpeed(speed);

    ui->indicator_msg->setText(QString::number(speed) + " %");
}

void MainWindow::speed_reset()
{
    if(gif_animation == NULL) return;

    speed = 100;

    gif_animation->setSpeed(speed);

    ui->indicator_msg->setText(QString::number(speed) + " %");
}

void MainWindow::frame_plus()
{
    if(gif_animation == NULL) return;

    if(pp_status) gif_animation->stop();

    pp_status = false;

    gif_animation->jumpToNextFrame();

    pp_btn_change();
}

void MainWindow::frame_minus()
{
    if(gif_animation == NULL) return;

    if(pp_status) gif_animation->stop();

    pp_status = false;

    for(int i{0}; i < (gif_animation->currentFrameNumber() - 1); i++) gif_animation->jumpToNextFrame();

    pp_btn_change();
}

void MainWindow::set_sys()
{
    ui->exit_btn->setIcon(QIcon("image/s_exit.png"));
    ui->exit_btn->setIconSize(QSize(30, 30));

    ui->option_btn->setIcon(QIcon("image/s_settings.png"));
    ui->option_btn->setIconSize(QSize(30, 30));

    ui->pp_btn->setIcon(QIcon("image/s_play.png"));
    ui->pp_btn->setIconSize(QSize(30, 30));

    ui->prev_frame_btn->setIcon(QIcon("image/s_prev_frame.png"));
    ui->prev_frame_btn->setIconSize(QSize(30, 30));

    ui->next_frame_btn->setIcon(QIcon("image/s_next_frame.png"));
    ui->next_frame_btn->setIconSize(QSize(30, 30));

    ui->speed_minus->setIcon(QIcon("image/s_minus.png"));
    ui->speed_minus->setIconSize(QSize(30, 30));

    ui->speed_plus->setIcon(QIcon("image/s_plus.png"));
    ui->speed_plus->setIconSize(QSize(30, 30));

    ui->speed_re->setIcon(QIcon("image/s_reset.png"));
    ui->speed_re->setIconSize(QSize(30, 30));
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
    this->setStyleSheet("background-color: #363636;");

    ui->gif_place->setStyleSheet("QLabel{"
                                 "font-family: \"DejaVu Sans\", \"Georgia\";"
                                 "font-size: 32px;"
                                 "color: #ffffff;"
                                 "background-color: #363636;"
                                 "border-radius: 0px;"
                                 "border: 2px solid #ff4d00;"
                                 "}");

    ui->exit_btn->setIcon((QIcon("image/o_exit.png")));
    ui->exit_btn->setIconSize(QSize(24, 24));
    ui->exit_btn->setStyleSheet("QPushButton{"
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

    ui->option_btn->setIcon((QIcon("image/o_settings.png")));
    ui->option_btn->setIconSize(QSize(24, 24));
    ui->option_btn->setStyleSheet("QPushButton{"
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

    ui->open_btn->setStyleSheet("QPushButton{"
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

    ui->pp_btn->setIcon((QIcon("image/o_play.png")));
    ui->pp_btn->setIconSize(QSize(24, 24));
    ui->pp_btn->setStyleSheet("QPushButton{"
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

    ui->speed_msg->setStyleSheet("QLabel{"
                                 "font-family: \"DejaVu Sans\", \"Georgia\";"
                                 "color: #ffffff;"
                                 "border-radius: 0px;"
                                 "border-left: 2px solid #ff4d00;"
                                 "border-top: 2px solid #ff4d00;"
                                 "padding-left: 4px;"
                                 "}");

    ui->prev_frame_btn->setIcon((QIcon("image/o_prev_frame.png")));
    ui->prev_frame_btn->setIconSize(QSize(24, 24));
    ui->prev_frame_btn->setStyleSheet("QPushButton{"
                                "font-family: \"DejaVu Sans\", \"Georgia\";"
                                "font-size: 14px;"
                                "background-color: #363636;"
                                "color: #ffffff;"
                                "border-radius: 0px;"
                                "border-top: 2px solid #ff4d00;"
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

    ui->next_frame_btn->setIcon((QIcon("image/o_next_frame.png")));
    ui->next_frame_btn->setIconSize(QSize(24, 24));
    ui->next_frame_btn->setStyleSheet("QPushButton{"
                                "font-family: \"DejaVu Sans\", \"Georgia\";"
                                "font-size: 14px;"
                                "background-color: #363636;"
                                "color: #ffffff;"
                                "border-radius: 0px;"
                                "border-top: 2px solid #ff4d00;"
                                "border-right: 2px solid #ff4d00;"
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

    ui->indicator_msg->setStyleSheet("QLabel{"
                                     "font-family: \"DejaVu Sans\", \"Georgia\";"
                                     "color: #ffffff;"
                                     "border-radius: 0px;"
                                     "border-left: 2px solid #ff4d00;"
                                     "border-bottom: 2px solid #ff4d00;"
                                     "padding-left: 4px;"
                                     "}");

    ui->speed_minus->setIcon(QIcon("image/o_minus.png"));
    ui->speed_minus->setIconSize(QSize(24, 24));
    ui->speed_minus->setStyleSheet("QPushButton{"
                                   "font-family: \"DejaVu Sans\", \"Georgia\";"
                                   "font-size: 14px;"
                                   "background-color: #363636;"
                                   "color: #ffffff;"
                                   "border-radius: 0px;"
                                   "border-bottom: 2px solid #ff4d00;"
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

    ui->speed_plus->setIcon(QIcon("image/o_plus.png"));
    ui->speed_plus->setIconSize(QSize(24, 24));
    ui->speed_plus->setStyleSheet("QPushButton{"
                                   "font-family: \"DejaVu Sans\", \"Georgia\";"
                                   "font-size: 14px;"
                                   "background-color: #363636;"
                                   "color: #ffffff;"
                                   "border-radius: 0px;"
                                   "border-bottom: 2px solid #ff4d00;"
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

    ui->speed_re->setIcon(QIcon("image/o_reset.png"));
    ui->speed_re->setIconSize(QSize(24, 24));
    ui->speed_re->setStyleSheet("QPushButton{"
                                   "font-family: \"DejaVu Sans\", \"Georgia\";"
                                   "font-size: 14px;"
                                   "background-color: #363636;"
                                   "color: #ffffff;"
                                   "border-radius: 0px;"
                                   "border-bottom: 2px solid #ff4d00;"
                                   "border-right: 2px solid #ff4d00;"
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

void MainWindow::pp_btn_change()
{
    if(pp_status == true){
        if(get_param(THEME) == "system"){
            ui->pp_btn->setIcon(QIcon("image/s_pause.png"));
            ui->pp_btn->setIconSize(QSize(30, 30));
        }
        else if(get_param(THEME) == "oranje"){
            ui->pp_btn->setIcon(QIcon("image/o_pause.png"));
            ui->pp_btn->setIconSize(QSize(30, 30));
        }
        else{
            ui->pp_btn->setIcon(QIcon("image/m_pause.png"));
            ui->pp_btn->setIconSize(QSize(30, 30));
        }
    }
    else{
        if(get_param(THEME) == "system"){
            ui->pp_btn->setIcon(QIcon("image/s_play.png"));
            ui->pp_btn->setIconSize(QSize(30, 30));
        }
        else if(get_param(THEME) == "oranje"){
            ui->pp_btn->setIcon(QIcon("image/o_play.png"));
            ui->pp_btn->setIconSize(QSize(30, 30));
        }
        else{
            ui->pp_btn->setIcon(QIcon("image/m_play.png"));
            ui->pp_btn->setIconSize(QSize(30, 30));
        }
    }
}
