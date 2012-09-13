#ifndef SHIP_H
#define SHIP_H

#include <point2D.h>

class Ship
{
public:

    Ship();
    ~Ship();
    void draw();
    void drawHitBox();

    float yAngle;
    float xPos;
    float zPos;
    double yRadian;
    float cosRad;
    float sinRad;
    float cosMrad;
    float sinMrad;

    float hitboxMaxX;
    float hitboxMinX;
    float hitboxMaxZ;
    float hitboxMinZ;

    bool forwardKeyPressed;
    bool backwardKeyPressed;
    bool rightdKeyPressed;
    bool leftKeyPressed;

    Point2D topRight;
    Point2D topLeft;
    Point2D bottomRight;
    Point2D bottomLeft;

    void updateVaribles();
    void updateHitbox();

private:
    Point2D defaultTopRight;
    Point2D defaultTopLeft;
    Point2D defaultBottomRight;
    Point2D defaultBottomLeft;

    Point2D *hitBoxCorners[4];

    Point2D updatePoint(Point2D *defaultPoint);
};
#endif // SHIP_H
