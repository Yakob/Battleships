#ifndef UTILS_H
#define UTILS_H

#include <point2D.h>

class Utils {
public:
    double getRadian(float degree);
    Point2D rotatePoint(Point2D *point, double radian);
    Point2D rotateAndTranslatePoint(Point2D *point, double radian, float x, float y);
    void getLimits(Point2D **sourcePoints, float *limits);
};

#endif // UTILS_H
