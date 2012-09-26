#include <missile.h>

Missile::Missile(float x, float z, float angle) {
    this->x = x;
    this->startX = x;
    this->z = z;
    this->startZ = z;
    this->angle = angle;
}

bool Missile::update() {
    return true;
}

void Missile::move() {

}

void Missile::draw() {

}
