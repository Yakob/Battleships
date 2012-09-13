#include <point2D.h>

Point2D::Point2D() {}

Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Point2D::~Point2D() {}

void Point2D::set(float x, float y) {
    this->x = x;
    this->y = y;
}
