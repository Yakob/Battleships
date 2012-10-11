#ifndef UTILS_H
#define UTILS_H

#include <point2D.h>

class Utils {
public:
    double getRadian(float degree);
    float getDistance(Point2D* pointA, Point2D* pointB);
};

#endif // UTILS_H
