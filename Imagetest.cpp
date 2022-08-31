#include<iostream>
#include"Image.h"
using namespace std;

#ifndef WINDOW_NAME
#define WINDOW_NAME "Images"
#endif

//set saveDir
int main()
{    
    //��ʼ��
    int index=0;//ȫ�ֱ�������¼��ǰչʾ��ͼƬ�������±�(0 to n-1)
    int display=0;//ȫ�ֱ�������ΪDisplay�����Ĳ������ֱ������ʾԭͼ������ʾ��ǽǵ�ͼ������ʾ͸�ӱ任��ĳ�Ʒͼ��
    namedWindow(WINDOW_NAME);
    Image::validMouse = false;

    //����ͼƬ��
    //�ṩ������·�����顢�ļ���������������:Image���������
    string dirstr[4];//��Qt or cin �ṩ
        dirstr[0]="testsource/1.jpg";
        dirstr[1]="testsource/2.jpg";
        dirstr[2]="testsource/3.jpg";
        dirstr[3]="testsource/4.jpg";
    Image *img;
        int imgcount=4;//�������룬���û��ṩ
        img=new Image[imgcount];
        for(int i=0; i<imgcount; i++)
        {
            Image t_img(dirstr[i]);
            img[i] = t_img;
        }
        
    //���
    //������ɣ����ͼƬ����¼�ǵ�
    for(int i=0; i<imgcount; i++)
    {
        img[i].Detect();
    }
    display = 1;

    //չʾ���ͼ���ֶ��޸�
    //����ɹ����������޸Ľǵ�λ�ã��յ�Qt��ȷ�ϡ��źź��˳����˴��á�Enter��������
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
        else if(Key == 27)//ģ������� Esc
            return 0;
        else if(Key == 13)//ģ��ȷ�ϼ� Enter
        {
            Image::validMouse = false;
            break;
        }
        img[index%imgcount].Display(display);//����index�Ǹ��������
    }

    //͸�ӱ任
    //������ɣ�����ת��ͼ
    for(int i=0; i<imgcount; i++)
    {
        img[i].Transform();
    }
    display = 2;

    //չʾ�任ͼ
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
        else if(Key == 27)//ģ������� Esc
            break;
        img[index%imgcount].Display(display);
    }

    //post treatment
    delete []img;
    return 0;
}