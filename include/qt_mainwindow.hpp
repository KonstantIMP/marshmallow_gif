#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QMovie>

#include "../lib/queue.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void load_from_file(std::string);

    void open_gif();

private slots:
    void change_pp_status();

private:
    Ui::MainWindow *ui;

    void set_sys();
    void set_marsh();
    void set_or();

    bool pp_status;
    unsigned int speed;

    QMovie * gif_animation;

    void pp_btn_change();
};

#endif // MAINWINDOW_HPP
