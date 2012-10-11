#ifndef MISSILE_H
#define MISSILE_H

#include <utils.h>
#include <hitbox.h>
#include <ship.h>

class Missile : public Hitbox {
public:
    Missile(float x, float z, float angle, Ship* player);
    ~Missile();
    bool isOutOfFuel();
    void move();
    void draw();
    float angle;
    float x;
    float z;
    Ship* player;
private:
    float startX;
    float startZ;
    double radian;
    Utils utils;
};

#endif // MISSILE_H
