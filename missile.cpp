#include <missile.h>
#include <math.h>
#include <utils.h>
#include <GL/glut.h>

#define SHOT_LENGTH 60.0f
#define MISSILE_SPEED 0.4f

Missile::Missile(float x, float z, float angle) {
    this->x = x;
    this->startX = x;
    this->z = z;
    this->startZ = z;
    this->angle = angle;
}

Missile::~Missile(){}

bool Missile::update() {
    if(sqrt(pow((startX - x), 2) + pow((startZ - z), 2) > SHOT_LENGTH)) {
        this->~Missile();
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
    glTranslatef(0, 0.2, -0.6);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.33f, 0.33f, 0.33f);
    gluCylinder(obj, 0, 0.07, 0.001, 30, 30);
    gluCylinder(obj, 0.07, 0.07, 0.2, 30, 30);
    glTranslatef(0, 0, 0.2f);
    gluCylinder(obj, 0.07, 0, 0.2, 30, 30);
}
