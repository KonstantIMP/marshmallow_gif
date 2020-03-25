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

    void get_lang();
};

#endif // QT_START_SETUP_HPP
