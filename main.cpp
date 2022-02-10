#include"Ball/Ball.h"
#include "iostream"

using namespace cv;
using namespace std;

Mat img = Mat::zeros(Size(Win_Width, Win_Height), CV_8UC3);
Mat temp = img.clone();
bool flag = false;
vector<Ball> A;
//vector<Rec> B;

void on_mouse(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDOWN) {
        flag = true;
        Point C = Point(x, y);
        cout << "L_Down" << endl;
        Ball ball = Ball(Point(x, y), 1, 0, 0);
        A.push_back(ball);
        while (1) {
            Mat temp = img.clone();
            A[A.size() - 1].ReR();
            for (vector<Ball>::iterator it = A.begin(); it != A.end(); ++it) {
                (*it).Refresh();
                circle(temp, (*it).Get_point(), (*it).Get_r(), Scalar(0, 0, 255), -1, 8, 0);
            }
            for (vector<Ball>::iterator it = A.begin(); it != A.end(); ++it) {
                for (vector<Ball>::iterator i = it + 1; i != A.end(); ++i) {
                    (*i).IsCollideWithBall(it);
                }
                (*it).IsCollidewithwall();
            }
            imshow("temp", temp);
            waitKey(20);
            if (flag == false)
                break;
        }
    }
    if (event == EVENT_LBUTTONUP) {
        flag = false;
        A[A.size() - 1].EndBuild();
    }
}

int main() {
    vector<Ball>::iterator it = A.begin();
    namedWindow("temp");
    imshow("temp", img);
//    Rec R = Rec(Point(0, 0), 200, 300, 10);
//    Rec R1 = Rec(Point(Win_Width - 200, 0), 200, 300, -10);
//    /*temp1.EndBuild(), temp2.EndBuild();*/
//    B.push_back(R);
//    vector<Rec>::iterator It = B.begin();
    /*A.push_back(temp);
    A.push_back(temp2);*/
    while (1) {
        Mat temp = img.clone();
        setMouseCallback("temp", on_mouse);
//        for (It = B.begin(); It != B.end(); ++It)
//        {
//            It->Refresh();
//            rectangle(temp, It->Get_Rec(), Scalar(255, 255, 255), -1, 8, 0);
//        }
//        for (It = B.begin(); It != B.end(); ++It)
//        {
//            for (vector<Rec>::iterator i = It + 1; i != B.end(); ++i)
//            {
//                i->IsCollideWithRec(It);
//            }
//            for (vector<Ball>::iterator i = A.begin(); i != A.end(); ++i)
//                It->IsCollideWithBall(i);
//            It->IsCollideWithWall();
//        }



        for (it = A.begin(); it != A.end(); ++it) {
            (*it).Refresh();
            circle(temp, (*it).Get_point(), (*it).Get_r(), Scalar(0, 0, 255), -1, 8, 0);
        }
        for (it = A.begin(); it != A.end(); ++it) {
            for (vector<Ball>::iterator i = it + 1; i != A.end(); ++i) {
                (*i).IsCollideWithBall(it);
            }
            (*it).IsCollidewithwall();
        }
        imshow("temp", temp);
        waitKey(20);
    }
    waitKey(0);
    return 0;
}