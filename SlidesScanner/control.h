#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>

namespace Ui {
class control;
}

class control : public QMainWindow
{
    Q_OBJECT

public:
    explicit control(QWidget *parent = nullptr);
    ~control();

private slots:
    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::control *ui;
};

#endif // CONTROL_H
