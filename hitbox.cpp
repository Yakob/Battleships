#include <hitbox.h>

void Hitbox::updateHitbox(double sin, double cos, float x, float y) {
    for (int i = 0; i < baseHitbox.size(); ++i) {
        hitbox[i]->set(baseHitbox[i]->x*cos - baseHitbox[i]->y*sin + x,
                       baseHitbox[i]->x*sin + baseHitbox[i]->y*cos + y);
    }
}

void Hitbox::updateLimits() {
    minX = maxX = hitbox.at(0)->x;
    minZ = maxZ = hitbox.at(0)->y;

    Point2D* p;
    foreach (p, hitbox) {
        if(p->x < minX) minX = p->x;
        if(p->x > maxX) maxX = p->x;
        if(p->y < minZ) minZ = p->y;
        if(p->y > maxZ) maxZ = p->y;
    }
}

void Hitbox::createBaseHitboxPoint(float x, float y) {
    baseHitbox.append(new Point2D(x, y));
    hitbox.append(new Point2D(x, y));
}
