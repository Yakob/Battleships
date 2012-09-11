#include "GL/glu.h"

#include <ship.h>
#include <math.h>

#define OFFSET 0.1f
#define PI 3.141459f

Ship::Ship() {
    forwardKeyPressed = false;
    backwardKeyPressed = false;
    rightdKeyPressed = false;
    leftKeyPressed = false;
    mapCollision = false;
}

Ship::~Ship() {}

double Ship::yRadians() {
    return PI / 180 * yAngle;
}

void Ship::updateHitbox() {
    topRight.set(sin(yRadians())-0.5, cos(yRadians())-0.5);
    topLeft.set(-1,-1);
    bottomLeft.set(-1,1);
    bottomRight.set(1,1);
}

void Ship::drawHitBox() {
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(bottomLeft.x, 0.5f, bottomLeft.y);
        glVertex3f(topLeft.x, 0.5f, topLeft.y);
        glVertex3f(topRight.x, 0.5f, topRight.y);
        glVertex3f(bottomRight.x, 0.5f, bottomRight.y);
    glEnd();
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
