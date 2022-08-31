/********************************************************************************
** Form generated from reading UI file 'savefile.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEFILE_H
#define UI_SAVEFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_savefile
{
public:
    QWidget *centralwidget;
    QPushButton *confirmButton;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QToolButton *rotateButton;
    QPushButton *saveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *savefile)
    {
        if (savefile->objectName().isEmpty())
            savefile->setObjectName(QStringLiteral("savefile"));
        savefile->resize(223, 560);
        centralwidget = new QWidget(savefile);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        confirmButton = new QPushButton(centralwidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(50, 380, 112, 34));
        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName(QStringLiteral("prevButton"));
        prevButton->setGeometry(QRect(50, 210, 112, 34));
        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setGeometry(QRect(50, 290, 112, 34));
        rotateButton = new QToolButton(centralwidget);
        rotateButton->setObjectName(QStringLiteral("rotateButton"));
        rotateButton->setGeometry(QRect(80, 130, 61, 51));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/1.jpg"), QSize(), QIcon::Normal, QIcon::On);
        rotateButton->setIcon(icon);
        rotateButton->setIconSize(QSize(70, 70));
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(50, 430, 112, 34));
        savefile->setCentralWidget(centralwidget);
        menubar = new QMenuBar(savefile);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 223, 29));
        savefile->setMenuBar(menubar);
        statusbar = new QStatusBar(savefile);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        savefile->setStatusBar(statusbar);

        retranslateUi(savefile);

        QMetaObject::connectSlotsByName(savefile);
    } // setupUi

    void retranslateUi(QMainWindow *savefile)
    {
        savefile->setWindowTitle(QApplication::translate("savefile", "MainWindow", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("savefile", "\347\241\256\350\256\244", Q_NULLPTR));
        prevButton->setText(QApplication::translate("savefile", "\344\270\212\344\270\200\345\274\240", Q_NULLPTR));
        nextButton->setText(QApplication::translate("savefile", "\344\270\213\344\270\200\345\274\240", Q_NULLPTR));
        rotateButton->setText(QApplication::translate("savefile", "...", Q_NULLPTR));
        saveButton->setText(QApplication::translate("savefile", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class savefile: public Ui_savefile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEFILE_H
