#define WINDOW_NAME "Images"

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "highgui.hpp"
#include "highgui/highgui_c.h"
#include "imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

class Image
{
private:
    Mat srcImg, markedImg, dstImg; //存储原图、检测图和生成图；src=source,dst=destination
    Point2f points[4]; //无序点组
    string srcDir, dstDir;  //导入和导出路径
    static bool drawBox;//允许绘制开关
    static int pointIndex;//鼠标点击的点序号，仅限回调函数调用
public:
    Image();
    Image(String);
    Image(Image&);
    ~Image();
    void Display(int);
    void Save(string);
    void Detect();
    void Transform();
    void Rotate();

    bool Imported();
    bool Detected();
    bool Transformed();
    Image& operator=(Image&);
    Image* operator=(Image*);
    static bool validMouse;
    friend
        void onMouseClick(int event, int x, int y, int flags, void* param);
};

bool Image::validMouse = false;
bool Image::drawBox = false;
int Image::pointIndex = -1;

Image::Image()
{
    srcImg = imread("Source/lena.jpg");
    srcDir = "Source/lena.jpg";
}

Image::Image(String dir)
{
    Mat inputPic = imread(dir);
    srcImg = inputPic.clone();
    srcDir = dir;
    /*
    Mat  I;
    float size;
    size = 1200 / (float)srcImg.cols * srcImg.rows;
    Size ResImgSiz = Size(1200, size);
    resize(srcImg, I, ResImgSiz, CV_INTER_CUBIC);
    I.copyTo(srcImg);
    */
}

Image::Image(Image& r)
{
    srcImg = r.srcImg.clone();
    markedImg = r.markedImg.clone();
    dstImg = r.dstImg.clone();
    for (int i = 0; i < 4; i++)
        points[i] = r.points[i];
    srcDir = r.srcDir;
    dstDir = r.dstDir;
}

Image::~Image()
{
}

void Image::Display(int n)
{
    if (n == 0)
    {
        if (Imported())
        {
            resizeWindow(WINDOW_NAME, srcImg.cols, srcImg.rows);
            imshow(WINDOW_NAME, srcImg);
        }
        else
            cout << "图片未成功载入，请检查文件路径！" << endl;
    }
    if (n == 1)
    {
        if (Detected())
        {
            resizeWindow(WINDOW_NAME, markedImg.cols, markedImg.rows);
            imshow(WINDOW_NAME, markedImg);
        }
        else
            cout << "未检测到目标对象！" << endl;
    }
    if (n == 2)
    {
        if (Transformed())
        {
            resizeWindow(WINDOW_NAME, dstImg.cols, dstImg.rows);
            imshow(WINDOW_NAME, dstImg);
        }
        else
            cout << "图像透视变换失败，请检查！" << endl;
    }
}

void Image::Detect()
{
    //初始化
    Mat src = srcImg.clone();

    Mat source = src.clone();
    Mat bkup = src.clone();
    Mat img = src.clone();
    Mat img1 = Mat::zeros(src.rows, src.cols, CV_8UC3);
    Mat img2 = Mat::zeros(src.rows, src.cols, CV_8UC3);
    Mat img22 = Mat::zeros(src.rows, src.cols, CV_8UC3);
    Mat img3 = Mat::zeros(src.rows, src.cols, CV_8UC3);
    Mat img4 = Mat::zeros(src.rows, src.cols, CV_8UC3);

    cvtColor(img, img, CV_RGB2GRAY);
    medianBlur(img, img, 7);//中值滤波

    //获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
    //膨胀
    dilate(img, img, element);

    int intthreshold = 130;//二值化阈值
    threshold(img, img, intthreshold, 255, THRESH_BINARY);;   //二值化

     //获取自定义核
    Mat element3 = getStructuringElement(MORPH_RECT, Size(1, 1));
    //腐蚀使轮廓完整
    erode(img, img, element3);

    //边缘光滑
    int height = img.rows;
    int width = img.cols;
    blur(img, img1, Size(1, 1));
    for (int i = 0; i < height; i++)
    {
        uchar* p = img1.ptr<uchar>(i);
        for (int j = 0; j < width; j++)
        {
            if (p[j] < intthreshold)
                p[j] = 0;
            else p[j] = 255;
        }
    }

    //边缘提取
    Canny(img1, img1, 50, 120, 3);   //边缘提取
    vector<vector<Point>> contours;  //储存轮廓
    vector<Vec4i> hierarchy;
    findContours(img1, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);  //获取轮廓
    Mat linePic = Mat::zeros(src.rows, src.cols, CV_8UC3);
    for (int index = 0; index < contours.size(); index++) {
        drawContours(linePic, contours, index, Scalar(rand() & 255, rand() & 255, rand() & 255), 1, 8);
    }

    //最大轮廓
    vector<vector<Point>> polyContours(contours.size());
    int maxArea = 0;
    for (int index = 0; index < contours.size(); index++)
    {
        if (contourArea(contours[index]) > contourArea(contours[maxArea]))
            maxArea = index;
        approxPolyDP(contours[index], polyContours[index], 10, true);
    }

    drawContours(img22, polyContours, maxArea, Scalar(255, 255, 255), 1);


    //膨胀
    Mat element2 = getStructuringElement(MORPH_ELLIPSE, Size(1, 1)); //核，第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
    dilate(img22, img22, element2);  //膨胀，实现过程中发现，适当的膨胀很重要
    cvtColor(img22, img22, CV_RGB2GRAY);
    vector<Vec2f>lines;
    HoughLines(img22, lines, 1, CV_PI / 180, 120, 0, 0);//霍夫变换

    //绘制线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point2f pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1500 * (-b));
        pt1.y = cvRound(y0 + 1500 * (a));
        pt2.x = cvRound(x0 - 1500 * (-b));
        pt2.y = cvRound(y0 - 1500 * (a));
        line(img3, pt1, pt2, Scalar(255, 255, 255), 2, LINE_AA);
    }
    cvtColor(img3, img3, CV_RGB2GRAY);
    //腐蚀使线变细
    erode(img3, img3, element);

    //再来一次
    vector<Vec2f>lines2;
    HoughLines(img3, lines2, 1, CV_PI / 180, 355, 0, 0);

    double X[40];
    double Y[40];
    double K[40];
    for (size_t i = 0; i < lines2.size(); i++)
    {
        float rho = lines2[i][0];
        float theta = lines2[i][1];
        Point2f pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1500 * (-b));
        pt1.y = cvRound(y0 + 1500 * (a));
        pt2.x = cvRound(x0 - 1500 * (-b));
        pt2.y = cvRound(y0 - 1500 * (a));
        line(img4, pt1, pt2, Scalar(255, 255, 255), 2, LINE_AA);
        X[i] = x0;
        Y[i] = y0;
        K[i] = -tan(theta);
        cout << "line" << i << ":" << "X = " << K[i] << "Y + " << X[i] - K[i] * Y[i] << endl << "(" << x0 << " , " << y0 << ")" << endl;
    }
    cvtColor(img4, img4, CV_RGB2GRAY);

    //解方程
    double x[4], y[4];
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 2; j <= 3; j++)
        {
            if (i == 0)
            {
                y[j - 2] = (X[i] - K[i] * Y[i] - X[j] + K[j] * Y[j]) / (K[j] - K[i]);
                x[j - 2] = K[i] * (y[j - 2] - Y[i]) + X[i];
                cout << j - 2 << ":  " << "(" << x[j - 2] << " , " << y[j - 2] << ")" << endl;
            }
            else
            {
                y[j] = (X[i] - K[i] * Y[i] - X[j] + K[j] * Y[j]) / (K[j] - K[i]);
                x[j] = K[i] * (y[j] - Y[i]) + X[i];
                cout << j << ":  " << "(" << x[j] << " , " << y[j] << ")" << endl;
            }
        }
    }

    //更新Points值
    points[0].x = x[0];
    points[0].y = y[0];
    points[1].x = x[1];
    points[1].y = y[1];
    points[2].x = x[2];
    points[2].y = y[2];
    points[3].x = x[3];
    points[3].y = y[3];

    //Detect End
    markedImg = srcImg.clone();
    for (int i = 0; i < 4; i++)
        circle(markedImg, points[i], 8, Scalar(0, 0, 255), -1, 8);
}

void onMouseClick(int event, int x, int y, int flags, void* param)
{
    if (Image::validMouse == false)
        return;
    Image t_img = *(Image*)param;
    Point2f t_point(x, y);
    if (event == EVENT_LBUTTONDOWN)
    {
        for (int i = 0; i < 4; i++)
        {
            if (((x - t_img.points[i].x) * (x - t_img.points[i].x) + (y - t_img.points[i].y) * (y - t_img.points[i].y)) < 64)
            {
                Image::drawBox = 1;
                Image::pointIndex = i;
                circle(t_img.markedImg, t_img.points[Image::pointIndex], 8, Scalar(0, 255, 255), -1, 8);
                break;
            }
        }
    }
    else if (event == EVENT_MOUSEMOVE)
    {
        if (Image::drawBox)
        {
            t_img.points[Image::pointIndex] = t_point;
            t_img.markedImg = t_img.srcImg.clone();
            for (int i = 0; i < 4; i++)
                circle(t_img.markedImg, t_img.points[i], 8, Scalar(0, 0, 255), -1, 8);
            circle(t_img.markedImg, t_img.points[Image::pointIndex], 8, Scalar(0, 255, 255), -1, 8);
        }
    }
    else if (event == EVENT_LBUTTONUP)
    {
        if (Image::drawBox)
        {
            circle(t_img.markedImg, t_img.points[Image::pointIndex], 8, Scalar(0, 0, 255), -1, 8);
            Image::pointIndex = -1;
            Image::drawBox = 0;
        }
    }
    *(Image*)param = t_img;
}

void Image::Transform()
{
    //Sort 点排序模块
    //赋值
    Point2f srcPoints[4];
    for (int i = 0; i < 4; i++)
        srcPoints[i] = points[i];
    //设定center
    Point2f center;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (srcPoints[j].x > srcPoints[i].x)
            {
                Point2f t_Point;
                t_Point = srcPoints[j];
                srcPoints[j] = srcPoints[i];
                srcPoints[i] = t_Point;
            }
        }
    }
    center.x = (srcPoints[1].x + srcPoints[2].x) / 2;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (srcPoints[j].y > srcPoints[i].y)
            {
                Point2f t_Point;
                t_Point = srcPoints[j];
                srcPoints[j] = srcPoints[i];
                srcPoints[i] = t_Point;
            }
        }
    }
    center.y = (srcPoints[1].y + srcPoints[2].y) / 2;
    for (int i = 0; i < 4; i++)
    {
        if (srcPoints[i].x < center.x && srcPoints[i].y < center.y)
            points[0] = srcPoints[i];
        else if (srcPoints[i].x<center.x && srcPoints[i].y>center.y)
            points[1] = srcPoints[i];
        else if (srcPoints[i].x > center.x && srcPoints[i].y > center.y)
            points[2] = srcPoints[i];
        else if (srcPoints[i].x > center.x && srcPoints[i].y < center.y)
            points[3] = srcPoints[i];
        //Todo:考虑点在坐标轴上的情形
    }

    //透视变换模块
    Point2f dstPoints[4]{ Point2f(0, 0), Point2f(0, 900), Point2f(1200, 900), Point2f(1200, 0) };
    Mat Trans = getPerspectiveTransform(points, dstPoints);//得到透视变换矩阵
    warpPerspective(srcImg, dstImg, Trans, Size(1200, 900), CV_INTER_CUBIC);
    //warpPerspective(srcImg, dstImg, Trans, Size(srcImg.cols, srcImg.rows), CV_INTER_CUBIC);
    dstImg = dstImg(Range(0, 900), Range(0, 1200));//裁剪模块
}

void Image::Rotate()
{
    Point2f center(dstImg.rows / 2, dstImg.rows / 2);
    Mat rotmat = getRotationMatrix2D(center, -90, 1);
    Mat temp(dstImg.cols, dstImg.rows, CV_8UC3);
    warpAffine(dstImg, temp, rotmat, temp.size());
    dstImg = temp.clone();
}

void Image::Save(string dst)
{
    //Denoise
    fastNlMeansDenoisingColored(dstImg, dstImg);

    //Save
    string temp = "/";
    dstDir = dst + "/transformed_" + srcDir.substr(srcDir.find_last_of(temp) + 1);
    imwrite(dstDir, dstImg);
}

bool Image::Imported()
{
    return !srcImg.empty();
}

bool Image::Detected()
{
    return !markedImg.empty();
}

bool Image::Transformed()
{
    return !dstImg.empty();
}

Image& Image::operator=(Image& r)
{
    srcImg = r.srcImg.clone();
    markedImg = r.markedImg.clone();
    dstImg = r.dstImg.clone();
    for (int i = 0; i < 4; i++)
        points[i] = r.points[i];
    srcDir = r.srcDir;
    dstDir = r.dstDir;
    return *this;
}

Image* Image::operator=(Image* p)
{
    *this = *p;
    return this;
}
