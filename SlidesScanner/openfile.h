#ifndef OPENFILE_H
#define OPENFILE_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QImage>
#include<QString>
#include <QTextCodec>
#include <QMessageBox>
#include<iostream>
#include"control.h"
using namespace std;
#include "opencv2/opencv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class openfile; }
QT_END_NAMESPACE

class openfile : public QMainWindow
{
    Q_OBJECT

public:
    openfile(QWidget *parent = nullptr);
    ~openfile();
    QList<QImage>   m_qlistLoadImgs;//用来存放用户选择的图片
    QPixmap *m_crtPixmap; //显示其中某张图片用

private slots:

    void on_openButton_clicked();

private:
    Ui::openfile *ui;
};
#endif // OPENFILE_H
