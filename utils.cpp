#include <utils.h>
#include <math.h>

#define PI 3.141459f

double Utils::getRadian(float degree) {
    return PI / 180 * degree;
}

float Utils::getDistance(Point2D *pointA, Point2D *pointB) {
    return sqrt(pow((pointA->x - pointB->x), 2) + pow((pointA->y - pointB->y), 2));
}
