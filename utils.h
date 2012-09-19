#ifndef UTILS_H
#define UTILS_H

#include <point2D.h>

class Utils {
public:
    double getRadian(float degree);
    void rotateAndTranslateHitBox(Point2D *source, Point2D *target, double radian, float x, float y);
    void getLimits(Point2D *sourcePoints, float *limits);
};

#endif // UTILS_H
