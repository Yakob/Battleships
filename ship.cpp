#include "GL/glu.h"

#include <ship.h>
#include <math.h>
#include <QDebug>

#define PI 3.141459f

Ship::Ship() {
    forwardKeyPressed = false;
    backwardKeyPressed = false;
    rightdKeyPressed = false;
    leftKeyPressed = false;

    defaultTopRight.set(0.5f,-0.5f);
    defaultTopLeft.set(-0.5f,-0.5f);
    defaultBottomLeft.set(-0.5f,0.5f);
    defaultBottomRight.set(0.5f,0.5f);

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

void Ship::draw() {
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.8f, 0.3f);
        // Top face of quad
        glVertex3f(-0.5f, 1.0f, 0.5f); // Top right of quad
        glVertex3f(0.5f, 1.0f, 0.5f); // Top left of quad
        glVertex3f(0.5f, 1.0f, -0.5f); // Bottom left of quad
        glVertex3f(-0.5f, 1.0f, -0.5f); // Bottom right of quad
        // Bottom face of quad
        glVertex3f(-0.5f, 0.0f, 0.5f); // Top right of quad
        glVertex3f(0.5f, 0.0f, 0.5f); // Top left of quad
        glVertex3f(0.5f, 0.0f, -0.5f); // Bottom left of quad
        glVertex3f(-0.5f, 0.0f, -0.5f); // Bottom right of quad
        // Front face of quad
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 1.0f, -0.5f); // Top right of quad
        glVertex3f(-0.5f, 1.0f, -0.5f); // Top left of quad
        glVertex3f(-0.5f, 0.0f, -0.5f); // Bottom left of quad
        glVertex3f(0.5f, 0.0f, -0.5f); // Bottom right of quad
        // Back face of quad
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, 1.0f, 0.5f); // Top right of quad
        glVertex3f(-0.5f, 1.0f, 0.5f); // Top left of quad
        glVertex3f(-0.5f, 0.0f, 0.5f); // Bottom left of quad
        glVertex3f(0.5f, 0.0f, 0.5f); // Bottom right of quad
        // Left face of quad
        glColor3f(0.5f, 0.8f, 0.3f);
        glVertex3f(-0.5f, 1.0f, 0.5f); // Top right of quad
        glVertex3f(-0.5f, 1.0f, -0.5f); // Top left of quad
        glVertex3f(-0.5f, 0.0f, -0.5f); // Bottom left of quad
        glVertex3f(-0.5f, 0.0f, 0.5f); // Bottom right of quad
        // Right face of quad
        glVertex3f(0.5f, 1.0f, 0.5f); // Top right of quad
        glVertex3f(0.5f, 1.0f, -0.5f); // Top left of quad
        glVertex3f(0.5f, 0.0f, -0.5f); // Bottom left of quad
        glVertex3f(0.5f, 0.0f, 0.5f); // Bottom right of quad
    glEnd();
}
