#ifndef HITBOX_H
#define HITBOX_H

#include <QList>
#include <point2D.h>

class Hitbox {

public:
    QList<Point2D*> baseHitbox;
    QList<Point2D*> hitbox;
    float minX;
    float maxX;
    float minZ;
    float maxZ;

    void updateHitbox(double sin, double cos, float x, float y);
    void updateLimits();
};

#endif // HITBOX_H
