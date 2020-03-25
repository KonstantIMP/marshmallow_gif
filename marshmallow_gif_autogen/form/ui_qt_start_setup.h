/********************************************************************************
** Form generated from reading UI file 'qt_start_setup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_START_SETUP_H
#define UI_QT_START_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt_start_setup
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *hello_msg;
    QSpacerItem *horizontalSpacer_2;
    QLabel *thank_msg;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *lang_btn;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *theme_msg;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *system_msg;
    QPushButton *system_btn;
    QVBoxLayout *verticalLayout_2;
    QLabel *marsh_msg;
    QPushButton *marsh_btn;
    QVBoxLayout *verticalLayout_3;
    QLabel *or_msg;
    QPushButton *or_btn;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *ok_btn;

    void setupUi(QWidget *qt_start_setup)
    {
        if (qt_start_setup->objectName().isEmpty())
            qt_start_setup->setObjectName(QString::fromUtf8("qt_start_setup"));
        qt_start_setup->resize(412, 347);
        verticalLayout_5 = new QVBoxLayout(qt_start_setup);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        hello_msg = new QLabel(qt_start_setup);
        hello_msg->setObjectName(QString::fromUtf8("hello_msg"));
        hello_msg->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(hello_msg);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        thank_msg = new QLabel(qt_start_setup);
        thank_msg->setObjectName(QString::fromUtf8("thank_msg"));
        thank_msg->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(thank_msg);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        lang_btn = new QPushButton(qt_start_setup);
        lang_btn->setObjectName(QString::fromUtf8("lang_btn"));

        horizontalLayout_3->addWidget(lang_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        theme_msg = new QLabel(qt_start_setup);
        theme_msg->setObjectName(QString::fromUtf8("theme_msg"));
        theme_msg->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(theme_msg);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        system_msg = new QLabel(qt_start_setup);
        system_msg->setObjectName(QString::fromUtf8("system_msg"));
        system_msg->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(system_msg);

        system_btn = new QPushButton(qt_start_setup);
        system_btn->setObjectName(QString::fromUtf8("system_btn"));

        verticalLayout->addWidget(system_btn);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        marsh_msg = new QLabel(qt_start_setup);
        marsh_msg->setObjectName(QString::fromUtf8("marsh_msg"));
        marsh_msg->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(marsh_msg);

        marsh_btn = new QPushButton(qt_start_setup);
        marsh_btn->setObjectName(QString::fromUtf8("marsh_btn"));

        verticalLayout_2->addWidget(marsh_btn);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        or_msg = new QLabel(qt_start_setup);
        or_msg->setObjectName(QString::fromUtf8("or_msg"));
        or_msg->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(or_msg);

        or_btn = new QPushButton(qt_start_setup);
        or_btn->setObjectName(QString::fromUtf8("or_btn"));

        verticalLayout_3->addWidget(or_btn);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        ok_btn = new QPushButton(qt_start_setup);
        ok_btn->setObjectName(QString::fromUtf8("ok_btn"));

        horizontalLayout_4->addWidget(ok_btn);


        verticalLayout_5->addLayout(horizontalLayout_4);


        retranslateUi(qt_start_setup);

        QMetaObject::connectSlotsByName(qt_start_setup);
    } // setupUi

    void retranslateUi(QWidget *qt_start_setup)
    {
        qt_start_setup->setWindowTitle(QCoreApplication::translate("qt_start_setup", "Form", nullptr));
        hello_msg->setText(QString());
        thank_msg->setText(QString());
        lang_btn->setText(QString());
        theme_msg->setText(QString());
        system_msg->setText(QString());
        system_btn->setText(QString());
        marsh_msg->setText(QString());
        marsh_btn->setText(QString());
        or_msg->setText(QString());
        or_btn->setText(QString());
        ok_btn->setText(QCoreApplication::translate("qt_start_setup", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qt_start_setup: public Ui_qt_start_setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_START_SETUP_H
