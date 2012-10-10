#ifndef SHIP_H
#define SHIP_H

#include <point2D.h>
#include <utils.h>
#include <hitbox.h>

class Ship : public Hitbox
{
public:

    Ship();
    ~Ship();
    void draw(float r, float g, float b);

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
    bool shotKeyPressed;
    bool reload;

    void updateVaribles();
    void turnLeft();
    void turnRight();
    void moveForward();
    void moveBackward();

private:
    Utils utils;
};
#endif // SHIP_H
