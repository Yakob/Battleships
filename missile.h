#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile(float x, float z, float angle);
    ~Missile();
    void update();
    void move();
    void draw();
private:
    float x;
    float z;
    float startX;
    float startZ;
    float angle;
    double radian;
};

#endif // MISSILE_H
