#include "GL/glu.h"

#include <ship.h>
#include <math.h>
#include <QDebug>

#define PI 3.141459f
#define TURN_SPEED 4.0f
#define MOVE_SPEED 0.2f

Ship::Ship() {
    forwardKeyPressed = false;
    backwardKeyPressed = false;
    rightdKeyPressed = false;
    leftKeyPressed = false;
    shotKeyPressed = false;
    reload = false;

    defaultTopRight.set(0.55f,-0.55f);
    defaultTopLeft.set(-0.55f,-0.55f);
    defaultBottomLeft.set(-0.55f,0.55f);
    defaultBottomRight.set(0.55f,0.55f);

    hitBoxCorners[0] = topRight;
    hitBoxCorners[1] = topLeft;
    hitBoxCorners[2] = bottomRight;
    hitBoxCorners[3] = bottomLeft;

    defaultHitBox[0] = defaultTopRight;
    defaultHitBox[1] = defaultTopLeft;
    defaultHitBox[2] = defaultBottomRight;
    defaultHitBox[3] = defaultBottomLeft;

    limits[0] = hitboxMinX;
    limits[1] = hitboxMaxX;
    limits[2] = hitboxMinZ;
    limits[3] = hitboxMaxZ;

    updateVaribles();
}

Ship::~Ship() {}

void Ship::updateVaribles() {
    yRadian = utils.getRadian(yAngle);
    yMinusRadian = utils.getRadian(-yAngle);
    sinRad = sin(yRadian);
    cosRad = cos(yRadian);
    sinMrad = sin(-yRadian);
    cosMrad = cos(-yRadian);
    utils.rotateAndTranslateHitBox(defaultHitBox, hitBoxCorners, yMinusRadian, xPos, zPos);
    utils.getLimits(hitBoxCorners, limits);
}

void Ship::turnLeft() {
    yAngle += TURN_SPEED;
    if (yAngle > 360.0f) yAngle -= 360.0f;
}

void Ship::turnRight() {
    yAngle -= TURN_SPEED;
    if (yAngle < 0.0f) yAngle += 360.0f;
}

void Ship::moveForward() {
    xPos -= sinRad * MOVE_SPEED;
    zPos -= cosRad * MOVE_SPEED;
}

void Ship::moveBackward() {
    xPos += sinRad * MOVE_SPEED;
    zPos += cosRad * MOVE_SPEED;
}

void Ship::draw(float r, float g, float b) {
    glRotatef(180, 0, 1, 0);
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0.4, 1);
        glVertex3f(0.5, 0.4, 0.25);
        glVertex3f(0.25, 0.0, 0.25);
        glVertex3f(-0.25, 0.0, 0.25);
        glVertex3f(-0.5, 0.4, 0.25);
        glVertex3f(0.5, 0.4, 0.25);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3f(-0.5, 0.4, -1);
        glVertex3f(-0.5, 0.4, 0.25);
        glVertex3f(0.5, 0.4, -1);
        glVertex3f(0.5, 0.4, 0.25);
        glVertex3f(0.25, 0, -1);
        glVertex3f(0.25, 0, 0.25);
        glVertex3f(-0.25, 0, -1);
        glVertex3f(-0.25, 0, 0.25);
        glVertex3f(-0.5, 0.4, -1);
        glVertex3f(-0.5, 0.4, 0.25);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-0.5, 0.4, -1);
        glVertex3f(0.5, 0.4, -1);
        glVertex3f(0.25, 0, -1);
        glVertex3f(-0.25, 0, -1);
    glEnd();

    glColor3f(0.45f, 0.45f, 0.45f);
    glBegin(GL_QUADS);
        glVertex3f(-0.5, 0.4, 0);
        glVertex3f(0.5, 0.4, 0);
        glVertex3f(0.25, 0.8, 0);
        glVertex3f(-0.25, 0.8, 0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3f(-0.5, 0.4, -0.75);
        glVertex3f(-0.5, 0.4, 0.25);
        glVertex3f(-0.25, 0.8, -0.75);
        glVertex3f(-0.25, 0.8, 0.25);
        glVertex3f(0.25, 0.8, -0.75);
        glVertex3f(0.25, 0.8, 0.25);
        glVertex3f(0.5, 0.4, -0.75);
        glVertex3f(0.5, 0.4, 0.25);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, 0.4, -1);
        glVertex3f(-0.5, 0.4, -0.75);
        glVertex3f(-0.25, 0.8, -0.75);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-0.5, 0.4, -1);
        glVertex3f(0.5, 0.4, -1);
        glVertex3f(0.25, 0.8, -0.75);
        glVertex3f(-0.25, 0.8, -0.75);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.5, 0.4, -1);
        glVertex3f(0.5, 0.4, -0.75);
        glVertex3f(0.25, 0.8, -0.75);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex3f(-0.06, 0.801, -0.75);
        glVertex3f(0.06, 0.801, -0.75);
        glVertex3f(0.06, 0.801, 0.25);
        glVertex3f(-0.06, 0.801, 0.25);
    glEnd();

    glColor3f(0.45f, 0.45f, 0.45f);
    glTranslatef(0, 0.6, 0);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.1, 0.08, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(obj, 0.08, 0.08, 0, 30, 30);
}
