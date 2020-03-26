#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QMovie>

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

    void speed_plus();
    void speed_minus();

    void speed_reset();

    void frame_plus();
    void frame_minus();

private:
    Ui::MainWindow *ui;

    void pp_btn_change();

    void set_sys();
    void set_marsh();
    void set_or();

    bool pp_status;

    int speed;

    QMovie * gif_animation;
};

#endif // MAINWINDOW_HPP
