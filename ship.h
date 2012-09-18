#ifndef SHIP_H
#define SHIP_H

#include <point2D.h>
#include <utils.h>

class Ship
{
public:

    Ship();
    ~Ship();
    void draw();
    void drawHitBox();

    Point2D *hitBoxCorners[4];
    Point2D *defaultHitBox[4];
    float limits[4];

    float yAngle;
    float xPos;
    float zPos;
    double yRadian;
    double yMinusRadian;
    float cosRad;
    float sinRad;
    float cosMrad;
    float sinMrad;

    bool forwardKeyPressed;
    bool backwardKeyPressed;
    bool rightdKeyPressed;
    bool leftKeyPressed;

    void updateVaribles();

private:
    Utils utils;

    float hitboxMaxX;
    float hitboxMinX;
    float hitboxMaxZ;
    float hitboxMinZ;

    Point2D topRight;
    Point2D topLeft;
    Point2D bottomRight;
    Point2D bottomLeft;

    Point2D defaultTopRight;
    Point2D defaultTopLeft;
    Point2D defaultBottomRight;
    Point2D defaultBottomLeft;
};
#endif // SHIP_H
