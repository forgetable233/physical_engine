//
// Created by dcr on 2022/5/20.
//

#ifndef PHYSICAL_ENGINE_OBJECT_H
#define PHYSICAL_ENGINE_OBJECT_H
#define _USE_MATH_DEFINES

#define Gra 1
#define Win_Height 500
#define Win_Width 900

#include <vector>
#include <pthread.h>
#include <cmath>

#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

struct force {
    double F;
    double angle;
};

class object {
private:

public:
    bool building = true;

    double weight{};

    cv::Point center;

    std::vector<force> F;

    object() = default;

    object(cv::Point _point);

    ~object();
};


#endif //PHYSICAL_ENGINE_OBJECT_H
