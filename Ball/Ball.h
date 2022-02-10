//
// Created by dcr on 2022/2/10.
//

#ifndef PHYSICAL_ENGINE_BALL_H
#define PHYSICAL_ENGINE_BALL_H

#include "opencv2/opencv.hpp"
#include"vector"
#include"cmath"
#define Gra 1											// ����
#define Pi 3.14159265
#define Win_Height 500
#define Win_Width 900

using namespace std;
using namespace cv;

struct force{int N, arc;};
struct sag{Point be, end, dir;};

class Ball
{
    cv::Point center;									//Բ��λ��
    bool Building = true; vector<force> F;				//С���յ�����������
    int R, Sx, Sy, weight;								//�뾶��С,�ٶȶ���Ϊÿһ֡ǰ���������˴�Ĭ��Ϊ20msһ֡,�ٶȷ�x��y����������
    bool flag1 = false, flag2 = false;					//�ж��Ƿ�������ײ,��X��Y��

public:
    Ball() {};

    ~Ball();

    Ball(Point C, int r, int m_Sx, int m_Sy);		//���캯��

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
