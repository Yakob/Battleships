#include <QKeyEvent>
#include <QTimer>
#include "GL/gl.h"
#include "GL/glu.h"
#include <math.h>

#include <engine.h>

#define SEA_SIZE 10
#define TURN_SPEED 4.0f
#define MOVE_SPEED 0.2f

Engine::Engine() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(60);
}

Engine::~Engine() {}

void Engine::initializeGL() {
    qglClearColor(Qt::black);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    xAngle = 70;
    yAngle = 0;
    scale = 1.0f;
    gamePause = false;
    resetGame();
}

void Engine::resizeGL(int w, int h) {
    if(h == 0)
        h = 1;

    glViewport(0, 0 , w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90.0f, static_cast<GLfloat>(w)/h, 0.1f, 10000.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Engine::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 2.0f, -15.0f);
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);
    drawSea(SEA_SIZE);

    glPushMatrix();
    glTranslatef(player1.xPos, 0, player1.zPos);
    player1.drawHitBox();
    glRotatef(player1.yAngle, 0, 1, 0);
    player1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(player2.xPos, 0, player2.zPos);
    player2.drawHitBox();
    glRotatef(player2.yAngle, 0, 1, 0);
    player2.draw();
    glPopMatrix();
}

void Engine::update() {
    if(!gamePause)
    {
        if(player1.forwardKeyPressed) moveForward(&player1);
        if(player1.backwardKeyPressed) moveBackward(&player1);
        if(player1.rightdKeyPressed) turnRight(&player1);
        if(player1.leftKeyPressed) turnLeft(&player1);
        if(player2.forwardKeyPressed) moveForward(&player2);
        if(player2.backwardKeyPressed) moveBackward(&player2);
        if(player2.rightdKeyPressed) turnRight(&player2);
        if(player2.leftKeyPressed) turnLeft(&player2);
    }

    if(player1.forwardKeyPressed || player1.backwardKeyPressed ||
            player1.rightdKeyPressed || player1.leftKeyPressed)
    {player1.updateHitbox();}

    this->updateGL();
}

void Engine::resetGame() {
    player1.yAngle = 0.0;
    player1.xPos = SEA_SIZE - 3.0f;
    player1.zPos = SEA_SIZE - 3.0f;
    player1.updateHitbox();

    player2.yAngle = 225.0;
    player2.xPos = -SEA_SIZE + 3.0f;
    player2.zPos = -SEA_SIZE + 3.0f;
    player2.updateHitbox();
}

void Engine::checkCollisionShipMap(Ship *player) {

}

void Engine::turnLeft(Ship *player) {
    player->yAngle += TURN_SPEED;
    if (player->yAngle < 0.0) player->yAngle -= 360.0;
}

void Engine::turnRight(Ship *player) {
    player->yAngle -= TURN_SPEED;
    if (player->yAngle > 360.0) player->yAngle += 360.0;
}

void Engine::moveForward(Ship *player) {
    player->xPos -= sin(player->yRadians()) * MOVE_SPEED;
    player->zPos -= cos(player->yRadians()) * MOVE_SPEED;
}

void Engine::moveBackward(Ship *player) {
    player->xPos += sin(player->yRadians()) * MOVE_SPEED;
    player->zPos += cos(player->yRadians()) * MOVE_SPEED;
}

void Engine::keyPressEvent(QKeyEvent *event) {
    switch(event ->key()) {
    //game
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_P:
        gamePause ? gamePause = false : gamePause = true;
        break;
    case Qt::Key_N:
        resetGame();
        break;
    //camera
    case Qt::Key_2:
        xAngle -= 1;
        break;
    case Qt::Key_8:
        xAngle += 1;
        break;
    case Qt::Key_4:
        yAngle += 1;
        break;
    case Qt::Key_6:
        yAngle -= 1;
        break;
    case Qt::Key_Plus:
        scale += 0.1f;
        break;
    case Qt::Key_Minus:
        scale -= 0.1f;
        break;
    //player 1
    case Qt::Key_A:
        player1.leftKeyPressed = true;
        break;
    case Qt::Key_D:
        player1.rightdKeyPressed = true;
        break;
    case Qt::Key_W:
        player1.forwardKeyPressed = true;
        break;
    case Qt::Key_S:
        player1.backwardKeyPressed = true;
        break;
    //player 2
    case Qt::Key_Left:
        player2.leftKeyPressed = true;
        break;
    case Qt::Key_Right:
        player2.rightdKeyPressed = true;
        break;
    case Qt::Key_Up:
        player2.forwardKeyPressed = true;
        break;
    case Qt::Key_Down:
        player2.backwardKeyPressed = true;
        break;
    }
}

void Engine::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A:
        player1.leftKeyPressed = false;
        break;
    case Qt::Key_D:
        player1.rightdKeyPressed = false;
        break;
    case Qt::Key_W:
        player1.forwardKeyPressed = false;
        break;
    case Qt::Key_S:
        player1.backwardKeyPressed = false;
        break;
    case Qt::Key_Left:
        player2.leftKeyPressed = false;
        break;
    case Qt::Key_Right:
        player2.rightdKeyPressed = false;
        break;
    case Qt::Key_Up:
        player2.forwardKeyPressed = false;
        break;
    case Qt::Key_Down:
        player2.backwardKeyPressed = false;
        break;
    }
}

void Engine::drawSea(int size) {
    glBegin(GL_QUADS);
        glColor3f(0.03f, 0.43f, 0.83f);

        glVertex3f(size, 0.0f, -size); // Top right of quad
        glVertex3f(-size, 0.0f, -size); // Top left of quad
        glVertex3f(-size, 0.0f, size); // Bottom left of quad
        glVertex3f(size, 0.0f, size); // Bottom right of quad
    glEnd();
}
