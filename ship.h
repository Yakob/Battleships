#ifndef SHIP_H
#define SHIP_H

class Ship
{
public:

    Ship();
    ~Ship();
    void draw();

    float yAngle;
    float xPos;
    float zPos;

    bool forwardKeyPressed;
    bool backwardKeyPressed;
    bool rightdKeyPressed;
    bool leftKeyPressed;
};
#endif // SHIP_H
