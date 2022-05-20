//
// Created by dcr on 2022/2/10.
//

#include "Ball.h"

Ball::Ball(cv::Point C, int r, int m_Sx, int m_Sy) : object(C) {
    R = r;
    speedX = m_Sx;
    speedY = m_Sy;
    weight = r * 100;
}

void Ball::ReR() { R += 1; }

void Ball::Out() { cout << this->center << ' ' << this->speedX << ' ' << this->speedY << endl; }//输出些数据，debug的时候用的

void Ball::EndBuild() {
    building = false;
    weight = R * 10;
    F.push_back(force{Gra * weight, 90});
}

void Ball::IsCollideWithBall(vector<Ball>::iterator b) {
    double disx = ((double) this->center.x + (double) this->speedX) - ((double) (*b).center.x + (double) (*b).speedX);
    double disy = ((double) this->center.y + (double) this->speedY) - ((double) (*b).center.y + (double) (*b).speedY);
    double angle = atan(disy / disx);
    double dis = sqrt(disx * disx + disy * disy);

    if (dis < (double) this->R + (double) b->R) {
        b->flag1 = b->flag2 = flag1 = flag2 = true;
        cout << "Crash!!!" << endl;
        double OneBallNeedMove = (((double) this->R + (double) b->R) - dis) / 2;
        if (this->building) {
            b->flag1 = b->flag2 = true;
            b->speedX = -b->speedX;
            b->speedY = -b->speedY;
            if (b->center.x + b->speedX >= this->center.x + this->speedX) {
                b->center.x += static_cast<int>(OneBallNeedMove * 2 * cos(angle));
                b->center.y += static_cast<int>(OneBallNeedMove * 2 * sin(angle));
            } else {
                b->center.x -= static_cast<int>(OneBallNeedMove * 2 * cos(angle));
                b->center.y -= static_cast<int>(OneBallNeedMove * 2 * sin(angle));
            }
            return;
        }
        if (b->building) {
            this->flag1 = this->flag2 = true;
            this->speedX = -this->speedX;//更新速度
            this->speedY = -this->speedY;
            if ((b->center.x + b->speedX) >= (this->center.x + this->speedX)) {
                this->center.x += static_cast<int>(OneBallNeedMove * 2 * cos(angle));
                this->center.y += static_cast<int>(OneBallNeedMove * 2 * sin(angle));
            } else {
                this->center.x -= static_cast<int>(OneBallNeedMove * 2 * cos(angle));
                this->center.y -= static_cast<int>(OneBallNeedMove * 2 * sin(angle));
            }
            return;
        }
        if ((b->center.x + b->speedX) >= (this->center.x + this->speedX)) {
            this->center.x -= static_cast<int>(OneBallNeedMove * cos(angle));
            this->center.y -= static_cast<int>(OneBallNeedMove * sin(angle));
            b->center.x += static_cast<int>(OneBallNeedMove * cos(angle));
            b->center.y += static_cast<int>(OneBallNeedMove * sin(angle));
        } else {
            this->center.x += static_cast<int>(OneBallNeedMove * cos(angle));
            this->center.y += static_cast<int>(OneBallNeedMove * sin(angle));
            b->center.x -= static_cast<int>(OneBallNeedMove * cos(angle));
            b->center.y -= static_cast<int>(OneBallNeedMove * sin(angle));
        }
        /*更新速度*/

        double x1 = this->speedX * cos(angle) + this->speedY * sin(angle), x2 =
                b->speedX * cos(angle) + b->speedY * sin(angle);                    //正交后计算
        double y1 = -this->speedX * sin(angle) + this->speedY * cos(angle), y2 = -b->speedX * sin(angle) + b->speedY * cos(angle);
        double X1 = (((double) this->weight - (double) (*b).weight) * x1 + 2 * (double) (*b).weight * x2) /
                    ((double) this->weight + (double) (*b).weight);
        double X2 = (((double) (*b).weight - (double) this->weight) * x2 + 2 * (double) this->weight * x1) /
                    ((double) this->weight + (double) (*b).weight);
        this->speedX = X1 * cos(angle) - y1 * sin(angle), b->speedX = X2 * cos(angle) - y2 * sin(angle);
        this->speedY = X1 * sin(angle) + y1 * cos(angle), b->speedY = X2 * sin(angle) + y2 * cos(angle);
    }
}

void Ball::IsCollidewithwall() {
    if (center.x + R + speedX >= Win_Width || center.x - R + speedX <= 0) {
        speedX = -speedX;
        flag1 = true;
    }
    if (center.x + R > Win_Width) { center.x = Win_Width - R; }
    else if (center.x - R < 0) { center.x = R; }
    if (center.y + R + speedY >= Win_Height || center.y - R + speedY <= 0) {
        speedY = -speedY;
        flag2 = true;
    }
    if (center.y + R > Win_Height) { center.y = Win_Height - R; }
    else if (center.y - R < 0) { center.y = R; }
}

float *Ball::Fuc(Point axis) {
    double a = static_cast<double>(axis.x * center.x + axis.y * center.y);
    auto *B = new float[2];
    B[0] = a - R, B[1] = a + R;
    return B;
}

void Ball::Refresh() {
    if (!building) {
        double Fx = 0, Fy = 0, Ax, Ay;
        for (auto & i : F) {
            Fx += i.F * cos(i.angle * M_PI / 180);
            Fy += i.F * sin(i.angle * M_PI / 180);
        }
        Ax = round_double(Fx / weight);
        Ay = round_double(Fy / weight);

        if (!flag1) {
            speedX += static_cast<int>(Ax);
        }
        if (!flag2) {
            speedY += static_cast<int>(Ay);
        }

        /*refresh the position of the point*/
        center.x += speedX, center.y += speedY;
        flag1 = flag2 = false;
    }
    flag1 = flag2 = false;
}

Ball::~Ball() = default;
