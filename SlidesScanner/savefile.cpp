#include "savefile.h"
#include "ui_savefile.h"

extern int g_index;
extern int g_imgcount;
extern string g_dstStr;
extern bool g_rotate;

savefile::savefile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::savefile)
{
    ui->setupUi(this);
}

savefile::~savefile()
{
    delete ui;
}

void savefile::on_prevButton_clicked()
{
    g_index--;
    if (g_index < 0)
        g_index += g_imgcount;
}

void savefile::on_nextButton_clicked()
{
    g_index++;
    if (g_index >= g_imgcount)
        g_index -= g_imgcount;
}

void savefile::on_confirmButton_clicked()
{
    this->close();
}

void savefile::on_saveButton_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this,"请选择保存路径...","./");
    if(file_path.isEmpty())
    {
        QMessageBox mesg;
        mesg.warning(this,"warning","no folder found");
    }
    else
    {
        g_dstStr = file_path.toStdString();
        this->close();
    }
}

void savefile::on_rotateButton_clicked()
{
    g_rotate = 1;
}
