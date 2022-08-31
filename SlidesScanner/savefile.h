#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QMainWindow>
#include<QFileDialog>
#include<QScreen>
#include<iostream>
#include<QString>
#include <QMessageBox>
using namespace std;

namespace Ui {
class savefile;
}

class savefile : public QMainWindow
{
    Q_OBJECT

public:
    explicit savefile(QWidget *parent = nullptr);
    ~savefile();

private slots:
    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_confirmButton_clicked();

    void on_saveButton_clicked();

    void on_rotateButton_clicked();

private:
    Ui::savefile *ui;
};

#endif // SAVEFILE_H
