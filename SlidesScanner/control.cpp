#include "control.h"
#include "ui_control.h"

extern int g_index;
extern int g_imgcount;

control::control(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::control)
{
    ui->setupUi(this);
}

control::~control()
{
    delete ui;
}

void control::on_prevButton_clicked()
{
    g_index--;
    if (g_index < 0)
        g_index += g_imgcount;
}

void control::on_nextButton_clicked()
{
    g_index++;
    if (g_index >= g_imgcount)
        g_index -= g_imgcount;
}

void control::on_confirmButton_clicked()
{
    this->close();
}
