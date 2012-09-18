#include <utils.h>
#include <math.h>

#define PI 3.141459f

double Utils::getRadian(float degree) {
    return PI / 180 * degree;
}

Point2D Utils::rotatePoint(Point2D *point, double radian) {
    return Point2D(point->x * cos(radian) - point->y * sin(radian),
                   point->x * sin(radian) + point->y * cos(radian));
}

Point2D Utils::rotateAndTranslatePoint(Point2D *point, double radian, float x, float y) {
    return Point2D(point->x * cos(radian) - point->y * sin(radian) + x,
                   point->x * sin(radian) + point->y * cos(radian) + y);
}

void Utils::rotateAndTranslateHitBox(Point2D **source, Point2D **target, double radian, float x, float y) {
    for (int i = 0; i < 4; i++) {
        target[i]->set(source[i]->x * cos(radian) - source[i]->y * sin(radian) + x,
                       source[i]->x * sin(radian) + source[i]->y * cos(radian) + y);
    }
}

//limits [minX, maxX, minY, maxY]
void Utils::getLimits(Point2D **sourcePoints, float *limits) {
    limits[0] = limits[1] = sourcePoints[0]->x;
    limits[2] = limits[3] = sourcePoints[0]->y;

    for(int i = 1; i < 4; i++) {
        if(sourcePoints[i]->x < limits[0]) limits[0] = sourcePoints[i]->x;
        if(sourcePoints[i]->x > limits[1]) limits[1] = sourcePoints[i]->x;
        if(sourcePoints[i]->y < limits[2]) limits[2] = sourcePoints[i]->y;
        if(sourcePoints[i]->y > limits[3]) limits[3] = sourcePoints[i]->y;
    }
}
