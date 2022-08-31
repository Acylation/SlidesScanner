#include "openfile.h"
#include "control.h"
#include "savefile.h"
#include "image.h"
#include <QApplication>

int g_index = -1;
int g_display = 0;
string* g_dirStr;
string g_dstStr;
int g_imgcount = 0;
bool g_rotate=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    openfile w;
    control x;
    savefile y;

    //openfile
    w.show();
    while(1)
    {
        waitKey(15);
        if(w.isHidden())
            break;
    }

    //Import
    Image* img;
    img = new Image[g_imgcount];
    for (int i = 0; i < g_imgcount; i++)
    {
        Image t_img(g_dirStr[i]);
        img[i] = t_img;
    }

    img[0].Display(0);

    //Detect
    for (int i = 0; i < g_imgcount; i++)
    {
        img[i].Detect();
    }
    g_display = 1;

    //Edit
    namedWindow(WINDOW_NAME);
    moveWindow(WINDOW_NAME, w.geometry().x()+100, 0);
    x.show();
    x.move(100, x.geometry().y());
    Image::validMouse = true;
    g_index = 0;
    while (1)
    {
        waitKey(15);
        setMouseCallback(WINDOW_NAME, onMouseClick, (void*)&img[g_index]);
        img[g_index].Display(g_display);
        if (x.isHidden())
            break;
    }
    Image::validMouse = false;

    //Tranform
    for (int i = 0; i < g_imgcount; i++)
    {
        img[i].Transform();
    }
    //Post Treatment

    g_display = 2;

    //Display
    y.show();
    y.move(100, y.geometry().y());
    while (1)
    {
        waitKey(15);
        img[g_index].Display(g_display);
        if(g_rotate == 1)
        {
            img[g_index].Rotate();
            g_rotate = 0;
        }
        if (y.isHidden())
            break;
    }

    if(!g_dstStr.empty())
    {
        for (int i = 0; i < g_imgcount; i++)
            img[i].Save(g_dstStr);
    }

    destroyWindow(WINDOW_NAME);
    return 0;
}
