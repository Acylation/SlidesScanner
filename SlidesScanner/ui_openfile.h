/********************************************************************************
** Form generated from reading UI file 'openfile.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENFILE_H
#define UI_OPENFILE_H

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

class Ui_openfile
{
public:
    QWidget *centralwidget;
    QPushButton *openButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *openfile)
    {
        if (openfile->objectName().isEmpty())
            openfile->setObjectName(QStringLiteral("openfile"));
        openfile->resize(800, 409);
        centralwidget = new QWidget(openfile);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(310, 140, 181, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(15);
        openButton->setFont(font);
        openfile->setCentralWidget(centralwidget);
        menubar = new QMenuBar(openfile);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 29));
        openfile->setMenuBar(menubar);
        statusbar = new QStatusBar(openfile);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        openfile->setStatusBar(statusbar);

        retranslateUi(openfile);

        QMetaObject::connectSlotsByName(openfile);
    } // setupUi

    void retranslateUi(QMainWindow *openfile)
    {
        openfile->setWindowTitle(QApplication::translate("openfile", "openfile", Q_NULLPTR));
        openButton->setText(QApplication::translate("openfile", "\346\211\223\345\274\200\345\233\276\347\211\207", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class openfile: public Ui_openfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENFILE_H
