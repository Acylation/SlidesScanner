#include<iostream>
#include"Image.h"
using namespace std;

#ifndef WINDOW_NAME
#define WINDOW_NAME "Images"
#endif

//set saveDir
int main()
{    
    //初始化
    int index=0;//全局变量，记录当前展示的图片的数组下标(0 to n-1)
    int display=0;//全局变量，作为Display函数的参数，分别代表“显示原图”“显示标记角点图”“显示透视变换后的成品图”
    namedWindow(WINDOW_NAME);
    Image::validMouse = false;

    //导入图片组
    //提供参数：路径数组、文件数量，传出参数:Image类对象数组
    string dirstr[4];//由Qt or cin 提供
        dirstr[0]="testsource/1.jpg";
        dirstr[1]="testsource/2.jpg";
        dirstr[2]="testsource/3.jpg";
        dirstr[3]="testsource/4.jpg";
    Image *img;
        int imgcount=4;//可以输入，由用户提供
        img=new Image[imgcount];
        for(int i=0; i<imgcount; i++)
        {
            Image t_img(dirstr[i]);
            img[i] = t_img;
        }
        
    //检测
    //类内完成，标记图片并记录角点
    for(int i=0; i<imgcount; i++)
    {
        img[i].Detect();
    }
    display = 1;

    //展示检测图及手动修改
    //导入成功后启动，修改角点位置，收到Qt“确认”信号后退出，此处用“Enter”键代替
    Image::validMouse = true;
    while(1)
    {
        int Key = waitKey(15);
        setMouseCallback(WINDOW_NAME, onMouseClick, (void*) &img[index%imgcount]);
        if(Key == 'w')
            index--;
        else if(Key == 'a')
            index--;
        else if(Key == 's')
            index++;
        else if(Key == 'd')
            index++;
        else if(Key == 27)//模拟结束键 Esc
            return 0;
        else if(Key == 13)//模拟确认键 Enter
        {
            Image::validMouse = false;
            break;
        }
        img[index%imgcount].Display(display);//考虑index是负数的情况
    }

    //透视变换
    //类内完成，生成转换图
    for(int i=0; i<imgcount; i++)
    {
        img[i].Transform();
    }
    display = 2;

    //展示变换图
    while(1)
    {
        int Key = waitKey(15);
        if(Key == 'w')
            index--;
        else if(Key == 'a')
            index--;
        else if(Key == 's')
            index++;
        else if(Key == 'd')
            index++;
        else if(Key == 27)//模拟结束键 Esc
            break;
        img[index%imgcount].Display(display);
    }

    //post treatment
    delete []img;
    return 0;
}