//
// Created by dcr on 2022/2/10.
//

#ifndef PHYSICAL_ENGINE_BALL_H
#define PHYSICAL_ENGINE_BALL_H

#include "opencv2/opencv.hpp"
#include"vector"
#include"cmath"
#define Gra 1											// 重力
#define Pi 3.14159265
#define Win_Height 500
#define Win_Width 900

using namespace std;
using namespace cv;

struct force{int N, arc;};
struct sag{Point be, end, dir;};

class Ball
{
    cv::Point center;									//圆心位置
    bool Building = true; vector<force> F;				//小球收到的所有外力
    int R, Sx, Sy, weight;								//半径大小,速度定义为每一帧前进的量，此处默认为20ms一帧,速度分x，y，，，好算
    bool flag1 = false, flag2 = false;					//判断是否发生了碰撞,分X与Y轴

public:
    Ball() {};

    ~Ball();

    Ball(Point C, int r, int m_Sx, int m_Sy);		//构造函数

    int round_double(double number) { return (number > 0.0) ? (number + 0.5) : (number - 0.5); }

    Point Get_point(){return center;}

    int Get_r(){return R;}

    void IsCollideWithBall(vector<Ball>::iterator b);

    void IsCollidewithwall();

    void Refresh();

    void EndBuild();

    void ReR();

    void Out();

    float* Fuc(Point axis);

    int Get_Sx() { return Sx; }

    int Get_Sy() { return Sy; }

    int Get_Weight() { return weight; }

    void Change_Speed(int m_Sx, int m_Sy) { Sx = m_Sx, Sy = m_Sy; }

};


#endif //PHYSICAL_ENGINE_BALL_H
