#include <QKeyEvent>
#include <QTimer>
#include "GL/gl.h"
#include "GL/glu.h"
#include <math.h>
#include <QDebug>

#include <engine.h>

#define SEA_SIZE 10
#define TURN_SPEED 4.0f
#define MOVE_SPEED 0.2f
#define NEAR 2.0f

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
    playersMovment = false;
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
    glRotatef(player1.yAngle, 0, 1, 0);
    player1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(player2.xPos, 0, player2.zPos);
    glRotatef(player2.yAngle, 0, 1, 0);
    player2.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 2);
    player1.draw();
    glTranslatef(player2.xPos - player1.xPos, 0, player2.zPos - player1.zPos);
    glRotatef(player2.yAngle - player1.yAngle, 0, 1, 0);
    player2.draw();
    glPopMatrix();

    Missile* m;
    foreach(m, missilesList) {
        glPushMatrix();
        glTranslatef(m->x, 0.4, m->z);
        glRotatef(m->angle, 0, 1, 0);
        m->draw();
        glPopMatrix();
    }
}

void Engine::update() {
    player1_old = player1;
    player2_old = player2;

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
            player1.rightdKeyPressed || player1.leftKeyPressed) {
        player1.updateVaribles();
        playersMovment = true;
        if(checkCollisionShipMap(&player1)) player1 = player1_old;
    }

    if(player2.forwardKeyPressed || player2.backwardKeyPressed ||
            player2.rightdKeyPressed || player2.leftKeyPressed) {
        player2.updateVaribles();
        playersMovment = true;
        if(checkCollisionShipMap(&player2)) player2 = player2_old;
    }

    if(playersMovment) {
        if(checkPlayersNear() && checkCollisionShipShip()) {
            player1 = player1_old;
            player2 = player2_old;
        }
        playersMovment = false;
    }

    updateMissiles();

    //For debug purposes
    qDebug() << "Player 1";
    qDebug() << "x" << player1.xPos << "|z" << player1.zPos << "|a" << player1.yAngle;
    qDebug() << "maxX" << player1.limits[1] << "|minX" << player1.limits[0] <<
                "|maxZ" << player1.limits[3] << "|minZ" << player1.limits[2];
    qDebug() << "tr" << player1.hitBoxCorners[0].x << player1.hitBoxCorners[0].y <<
                "|tl" << player1.hitBoxCorners[1].x << player1.hitBoxCorners[1].y <<
                "|br" << player1.hitBoxCorners[2].x << player1.hitBoxCorners[2].y <<
                "|bl" << player1.hitBoxCorners[3].x << player1.hitBoxCorners[2].y;
    qDebug() << "";
    qDebug() << "Player 2";
    qDebug() << "x" << player2.xPos << "|z" << player2.zPos << "|a" << player2.yAngle;
    qDebug() << "maxX" << player2.limits[1] << "|minX" << player2.limits[0] <<
                "|maxZ" << player2.limits[3] << "|minZ" << player2.limits[2];
    qDebug() << "tr" << player2.hitBoxCorners[0].x << player2.hitBoxCorners[0].y <<
                "|tl" << player2.hitBoxCorners[1].x << player2.hitBoxCorners[1].y <<
                "|br" << player2.hitBoxCorners[2].x << player2.hitBoxCorners[2].y <<
                "|bl" << player2.hitBoxCorners[3].x << player2.hitBoxCorners[2].y;
    qDebug() << "";
    qDebug() <<"playersNear" << checkPlayersNear();

    this->updateGL();
}

void Engine::resetGame() {
    player1.yAngle = 45.0;
    player1.xPos = SEA_SIZE - 3.0f;
    player1.zPos = SEA_SIZE - 3.0f;
    player1.updateVaribles();

    player2.yAngle = 225.0;
    player2.xPos = -SEA_SIZE + 3.0f;
    player2.zPos = -SEA_SIZE + 3.0f;
    player2.updateVaribles();

    Missile* m;
    foreach (m, missilesList) {
        m->~Missile();
        m = NULL;
        missilesList.removeOne(m);
    }
}

bool Engine::checkCollisionShipMap(Ship *player) {
    return (player->limits[1] > SEA_SIZE || player->limits[0] < -SEA_SIZE ||
            player->limits[3] > SEA_SIZE || player->limits[2] < -SEA_SIZE)
            ? true : false;
}

bool Engine::checkPlayersNear() {
    return (sqrt(pow((player1.xPos - player2.xPos), 2) + pow((player1.zPos - player2.zPos), 2)) < NEAR)
            ? true : false;
}

bool Engine::checkCollisionShipShip() {
    Ship p1 = player1;
    Ship p2 = player2;

    p2.xPos -= p1.xPos;
    p2.zPos -= p1.zPos;
    p2.yAngle -= p1.yAngle;
    p2.updateVaribles();

    p1.xPos = 0;
    p1.zPos = 0;
    p1.yAngle = 0;
    p1.updateVaribles();

    for(int i = 0; i < 4; i++) {
        if(p2.hitBoxCorners[i].x > p1.limits[0] && p2.hitBoxCorners[i].x < p1.limits[1] &&
        p2.hitBoxCorners[i].y > p1.limits[2] && p2.hitBoxCorners[i].y < p1.limits[3]) return true;
    }

    p1 = player1;
    p2 = player2;

    p1.xPos -= p2.xPos;
    p1.zPos -= p2.zPos;
    p1.yAngle -= p2.yAngle;
    p2.updateVaribles();

    p2.xPos = 0;
    p2.zPos = 0;
    p2.yAngle = 0;
    p2.updateVaribles();

    for(int i = 0; i < 4; i++) {
        if(p1.hitBoxCorners[i].x > p2.limits[0] && p1.hitBoxCorners[i].x < p2.limits[1] &&
        p1.hitBoxCorners[i].y > p2.limits[2] && p1.hitBoxCorners[i].y < p2.limits[3]) return true;
    }

    return false;
}

void Engine::updateMissiles() {
    for (int i = 0; i < missilesList.size(); ++i) {
        if(missilesList[i]->update()) missilesList.removeAt(i);
    }
}

void Engine::turnLeft(Ship *player) {
    player->yAngle += TURN_SPEED;
    if (player->yAngle > 360.0f) player->yAngle -= 360.0f;
}

void Engine::turnRight(Ship *player) {
    player->yAngle -= TURN_SPEED;
    if (player->yAngle < 0.0f) player->yAngle += 360.0f;
}

void Engine::moveForward(Ship *player) {
    player->xPos -= player->sinRad * MOVE_SPEED;
    player->zPos -= player->cosRad * MOVE_SPEED;
}

void Engine::moveBackward(Ship *player) {
    player->xPos += player->sinRad * MOVE_SPEED;
    player->zPos += player->cosRad * MOVE_SPEED;
}

void Engine::shot(Ship *player) {
    Missile *missile = new Missile(player->xPos, player->zPos, player->yAngle);
    missilesList.append(missile);
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
    case Qt::Key_Space:
        shot(&player1);
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
