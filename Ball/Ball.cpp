//
// Created by dcr on 2022/2/10.
//

#include "Ball.h"

Ball::Ball(cv::Point C, int r, int m_Sx, int m_Sy){center = C;   R = r;  Sx = m_Sx;  Sy = m_Sy;   weight = r * 100;}

void Ball::ReR(){R += 1;}

void Ball::Out(){cout << this->center << ' ' << this->Sx << ' ' << this->Sy << endl;}//输出些数据，debug的时候用的

void Ball::EndBuild() { Building = false; weight = R * 10; F.push_back(force{ Gra * weight, 90 }); }

void Ball::IsCollideWithBall(vector<Ball>::iterator b)
{
    double disx = ((double)this->center.x + (double)this->Sx) - ((double)(*b).center.x + (double)(*b).Sx);
    double disy = ((double)this->center.y + (double)this->Sy) - ((double)(*b).center.y + (double)(*b).Sy);
    double angle = atan(disy / disx);
    double dis = sqrt(disx * disx + disy * disy);

    if (dis < (double)this->R + (double)b->R)
    {
        b->flag1 = b->flag2 = flag1 = flag2 = true;
        cout << "Crash!!!" << endl;
        double OneBallNeedMove = (((double)this->R + (double)b->R) - dis) / 2;
        if (this->Building)
        {
            b->flag1 = b->flag2 = true;
            b->Sx = -b->Sx;
            b->Sy = -b->Sy;
            if (b->center.x + b->Sx >= this->center.x + this->Sx)
            {
                b->center.x += OneBallNeedMove * 2 * cos(angle);
                b->center.y += OneBallNeedMove * 2 * sin(angle);
            }
            else
            {
                b->center.x -= OneBallNeedMove * 2 * cos(angle);
                b->center.y -= OneBallNeedMove * 2 * sin(angle);
            }
            return;
        }
        if (b->Building)
        {
            this->flag1 = this->flag2 = true;
            this->Sx = -this->Sx;//更新速度
            this->Sy = -this->Sy;
            if ((b->center.x + b->Sx) >= (this->center.x + this->Sx))
            {
                this->center.x += OneBallNeedMove * 2 * cos(angle);
                this->center.y += OneBallNeedMove * 2 * sin(angle);
            }
            else
            {
                this->center.x -= OneBallNeedMove * 2 * cos(angle);
                this->center.y -= OneBallNeedMove * 2 * sin(angle);
            }
            return;
        }
        if ((b->center.x + b->Sx) >= (this->center.x + this->Sx))
        {
            this->center.x -= OneBallNeedMove * cos(angle);
            this->center.y -= OneBallNeedMove * sin(angle);
            b->center.x += OneBallNeedMove * cos(angle);
            b->center.y += OneBallNeedMove * sin(angle);
        }
        else
        {
            this->center.x += OneBallNeedMove * cos(angle);
            this->center.y += OneBallNeedMove * sin(angle);
            b->center.x -= OneBallNeedMove * cos(angle);
            b->center.y -= OneBallNeedMove * sin(angle);
        }
        /*更新速度*/

        double x1 = this->Sx * cos(angle) + this->Sy * sin(angle), x2 = b->Sx * cos(angle) + b->Sy * sin(angle);					//正交后计算
        double y1 = -this->Sx * sin(angle) + this->Sy * cos(angle), y2 = -b->Sx * sin(angle) + b->Sy * cos(angle);
        double X1 = (((double)this->weight - (double)(*b).weight) * x1 + 2 * (double)(*b).weight * x2) / ((double)this->weight + (double)(*b).weight);
        double X2 = (((double)(*b).weight - (double)this->weight) * x2 + 2 * (double)this->weight * x1) / ((double)this->weight + (double)(*b).weight);
        this->Sx = X1 * cos(angle) - y1 * sin(angle), b->Sx = X2 * cos(angle) - y2 * sin(angle);
        this->Sy = X1 * sin(angle) + y1 * cos(angle), b->Sy = X2 * sin(angle) + y2 * cos(angle);
    }
}

void Ball::IsCollidewithwall()
{
    if (center.x + R + Sx >= Win_Width|| center.x - R + Sx <= 0){Sx = -Sx; flag1 = true;}
    if (center.x + R > Win_Width){center.x = Win_Width - R;}
    else if (center.x - R < 0){center.x = R;}
    if (center.y + R + Sy >= Win_Height || center.y - R + Sy <= 0){Sy = -Sy;flag2 = true;}
    if (center.y + R > Win_Height){center.y = Win_Height - R;}
    else if (center.y - R < 0){center.y = R;}
}

float* Ball::Fuc(Point axis)
{
    float a = axis.x * center.x + axis.y * center.y;
    float* B = new float[2];
    B[0] = a - R, B[1] = a + R;
    return B;
}

void Ball::Refresh()
{
    if (!Building)
    {
        double Fx = 0, Fy = 0, Ax, Ay;
        for (int i = 0; i < F.size(); i++)
        {
            Fx += F[i].N * cos(F[i].arc * Pi / 180);
            Fy += F[i].N * sin(F[i].arc * Pi / 180);
        }
        Ax = round_double(Fx / weight);
        Ay = round_double(Fy / weight);

        if (!flag1)
            Sx += Ax;
        if (!flag2)
            Sy += Ay;

        /*refresh the position of the point*/
        center.x += Sx, center.y += Sy;
        flag1 = flag2 = false;
    }
    flag1 = flag2 = false;
}

Ball::~Ball() {

}
