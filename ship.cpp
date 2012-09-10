#include "GL/glu.h"

#include <ship.h>
#include <math.h>

Ship::Ship() {
    forwardKeyPressed = false;
    backwardKeyPressed = false;
    rightdKeyPressed = false;
    leftKeyPressed = false;
}

Ship::~Ship() {}

void Ship::draw() {
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.8f, 0.3f);
        // Top face of quad
        glVertex3f(-0.5f, 1.0f, 0.5f); // Top right of quad
        glVertex3f(0.5f, 1.0f, 0.5f); // Top left of quad
        glVertex3f(0.5f, 1.0f, -0.5f); // Bottom left of quad
        glVertex3f(-0.5f, 1.0f, -0.5f); // Bottom right of quad
        // Bottom face of quad
        glVertex3f(-0.5f, 1.0f, 0.5f); // Top right of quad
        glVertex3f(0.5f, 1.0f, 0.5f); // Top left of quad
        glVertex3f(0.5f, 1.0f, -0.5f); // Bottom left of quad
        glVertex3f(-0.5f, 1.0f, -0.5f); // Bottom right of quad
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
