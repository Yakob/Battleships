#ifndef MISSILE_H
#define MISSILE_H

#include <utils.h>

class Missile {
public:
    Missile(float x, float z, float angle);
    ~Missile();
    bool update();
    void move();
    void draw();
    float angle;
    float x;
    float z;
private:
    float startX;
    float startZ;
    double radian;
    Utils utils;
};

#endif // MISSILE_H
