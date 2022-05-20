//
// Created by dcr on 2022/2/10.
//

#ifndef PHYSICAL_ENGINE_BALL_H
#define PHYSICAL_ENGINE_BALL_H

#include "../object.h"

using namespace std;
using namespace cv;
struct sag {
    Point be, end, dir;
};

class Ball : public object{
    int R{};                                //the length of the R. the speed the weight

    double speedX{};
    double speedY{};

    bool flag1 = false;                    //test whether the coll happened
    bool flag2 = false;

public:
    Ball() = default;;

    ~Ball();

    Ball(Point C, int r, int m_Sx, int m_Sy);        //constructor function

    static int round_double(double number) { return (number > 0.0) ? (number + 0.5) : (number - 0.5); }

    Point Get_point() { return center; }

    int Get_r() { return R; }

    void IsCollideWithBall(vector<Ball>::iterator b);

    void IsCollidewithwall();

    void Refresh();

    void EndBuild();

    void ReR();

    void Out();

    float *Fuc(Point axis);

    int Get_Sx() { return speedX; }

    int Get_Sy() { return speedY; }

    int Get_Weight() { return weight; }

    void Change_Speed(int m_Sx, int m_Sy) { speedX = m_Sx, speedY = m_Sy; }

};


#endif //PHYSICAL_ENGINE_BALL_H
