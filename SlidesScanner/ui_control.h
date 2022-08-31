/********************************************************************************
** Form generated from reading UI file 'control.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_control
{
public:
    QWidget *centralwidget;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *confirmButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *control)
    {
        if (control->objectName().isEmpty())
            control->setObjectName(QStringLiteral("control"));
        control->resize(269, 600);
        centralwidget = new QWidget(control);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName(QStringLiteral("prevButton"));
        prevButton->setGeometry(QRect(70, 200, 112, 34));
        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setGeometry(QRect(70, 280, 112, 34));
        confirmButton = new QPushButton(centralwidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(70, 370, 112, 34));
        control->setCentralWidget(centralwidget);
        menubar = new QMenuBar(control);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 269, 29));
        control->setMenuBar(menubar);
        statusbar = new QStatusBar(control);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        control->setStatusBar(statusbar);

        retranslateUi(control);

        QMetaObject::connectSlotsByName(control);
    } // setupUi

    void retranslateUi(QMainWindow *control)
    {
        control->setWindowTitle(QApplication::translate("control", "MainWindow", Q_NULLPTR));
        prevButton->setText(QApplication::translate("control", "\344\270\212\344\270\200\345\274\240", Q_NULLPTR));
        nextButton->setText(QApplication::translate("control", "\344\270\213\344\270\200\345\274\240", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("control", "\347\241\256\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class control: public Ui_control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
