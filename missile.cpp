#include <missile.h>
#include <math.h>
#include <utils.h>
#include <GL/glut.h>

#define SHOT_LENGTH 60.0f
#define MISSILE_SPEED 0.5f

Missile::Missile(float x, float z, float angle, Ship *player) {
    this->x = x;
    this->startX = x;
    this->z = z;
    this->startZ = z;
    this->angle = angle;
    this->player = player;

    createBaseHitboxPoint(0, -0.2f);
    createBaseHitboxPoint(0.07, 0);
    createBaseHitboxPoint(-0.07, 0);
    createBaseHitboxPoint(0.07, 0.2f);
    createBaseHitboxPoint(-0.07, 0.2f);
}

Missile::~Missile(){}

bool Missile::isOutOfFuel() {
    updateHitbox(sin(-utils.getRadian(angle)), cos(-utils.getRadian(angle)), x, z);
    updateLimits();
    if(sqrt(pow((startX - x), 2) + pow((startZ - z), 2) > SHOT_LENGTH)) {
        return true;
    } else {
        move();
        return false;
    }
}

void Missile::move() {
    x -= sin(utils.getRadian(angle)) * MISSILE_SPEED;
    z -= cos(utils.getRadian(angle)) * MISSILE_SPEED;
}

void Missile::draw() {
    GLUquadricObj *obj = gluNewQuadric();
    glTranslatef(0, 0.4f, 0.2f);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.33f, 0.33f, 0.33f);
    gluCylinder(obj, 0, 0.07, 0, 30, 30);
    gluCylinder(obj, 0.07, 0.07, 0.2, 30, 30);
    glTranslatef(0, 0, 0.2f);
    gluCylinder(obj, 0.07, 0, 0.2, 30, 30);
}
