#include "GL/glu.h"

#include <ship.h>
#include <math.h>

#define PI 3.141459f

Ship::Ship() {
    forwardKeyPressed = false;
    backwardKeyPressed = false;
    rightdKeyPressed = false;
    leftKeyPressed = false;
    mapCollision = false;

    defaultTopRight.set(0.6f,-0.6f);
    defaultTopLeft.set(-0.6f,-0.6f);
    defaultBottomLeft.set(-0.6f,0.6f);
    defaultBottomRight.set(0.6f,0.6f);

    hitboxCorners[0] = topRight;
    hitboxCorners[1] = topLeft;
    hitboxCorners[2] = bottomRight;
    hitboxCorners[3] = bottomLeft;
}

Ship::~Ship() {}

void Ship::updateVaribles() {
    yRadian = PI / 180 * yAngle;
    sinRad = sin(yRadian);
    cosRad = cos(yRadian);
    sinMrad = sin(-yRadian);
    cosMrad = cos(-yRadian);
}

Point2D Ship::updatePoint(Point2D *defaultPoint) {
    Point2D tempPoint;
    tempPoint.set(defaultPoint->x * cosMrad - defaultPoint->y * sinMrad + xPos,
                  defaultPoint->x * sinMrad + defaultPoint->y * cosMrad + zPos);
    return tempPoint;
}

void Ship::updateHitbox() {
    topRight = updatePoint(&defaultTopRight);
    topLeft = updatePoint(&defaultTopLeft);
    bottomLeft = updatePoint(&defaultBottomLeft);
    bottomRight = updatePoint(&defaultBottomRight);

    hitboxMaxX = hitboxMinX = topRight.x;
    hitboxMaxZ = hitboxMinZ = topRight.y;

    for(int i = 0; i < 4; i++) {
        if(hitboxCorners[i].x > hitboxMaxX) hitboxMaxX = hitboxCorners[i].x;
        if(hitboxCorners[i].x < hitboxMinX) hitboxMinX = hitboxCorners[i].x;
        if(hitboxCorners[i].y > hitboxMaxZ) hitboxMaxZ = hitboxCorners[i].y;
        if(hitboxCorners[i].y < hitboxMinZ) hitboxMinZ = hitboxCorners[i].y;
    }
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
