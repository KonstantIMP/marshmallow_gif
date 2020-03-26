#ifndef QT_START_SETUP_HPP
#define QT_START_SETUP_HPP

#include <QWidget>


namespace Ui {
class qt_start_setup;
}

class qt_start_setup : public QWidget
{
    Q_OBJECT

public:
    explicit qt_start_setup(QWidget *parent = nullptr);
    ~qt_start_setup();

private:
    Ui::qt_start_setup *ui;

    void set_ru();
    void set_en();

    void closeEvent(QCloseEvent *event);

private slots:
    void change_lang();

    void set_sys();
    void set_marsh();
    void set_or();
};

#endif // QT_START_SETUP_HPP
