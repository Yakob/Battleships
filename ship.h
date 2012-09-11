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

    bool mapCollision;
    bool forwardKeyPressed;
    bool backwardKeyPressed;
    bool rightdKeyPressed;
    bool leftKeyPressed;

    double yRadians();
    void updateHitbox();
    float getMaxTop();
    float getMaxBottom();
    float getMaxRight();
    float getMaxLeft();

private:
    Point2D topRight;
    Point2D topLeft;
    Point2D bottomRight;
    Point2D bottomLeft;

    void rotate(Point2D *point);
};
#endif // SHIP_H
