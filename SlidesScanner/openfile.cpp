#include "openfile.h"
#include "ui_openfile.h"

extern string* g_dirStr;
extern int g_imgcount;

openfile::openfile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::openfile)
{
    ui->setupUi(this);
}

openfile::~openfile()
{
    delete ui;
}

void openfile::on_openButton_clicked()
{
    QFileDialog fileDlg(this);
     fileDlg.setWindowTitle("Choose Pictures");
     QStringList qstrFilters;//设置文件过滤器的list
     qstrFilters<<"Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)";
     qstrFilters<<"Any files (*)";
     fileDlg.setNameFilters(qstrFilters);//设置文件过滤器
     fileDlg.setFileMode(QFileDialog::ExistingFiles);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile

     if(fileDlg.exec() == QDialog::Accepted)
    {
         QStringList strPathList = fileDlg.selectedFiles();//得到用户选择的多个文件的路径的list
         g_imgcount = strPathList.size();
         g_dirStr = new string[g_imgcount];
         for (int i = 0; i < strPathList.size(); i++)
             g_dirStr[i] = strPathList.at(i).toStdString();
         if(!m_qlistLoadImgs.empty())
         {
             m_qlistLoadImgs.clear();
         }
     }
     else
     {
         QMessageBox mesg;
         mesg.warning(this,"警告","没有找到图片哦！");
         return;
     }
     this->close();
}
