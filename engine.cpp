#include <QKeyEvent>
#include <QTimer>
#include "GL/gl.h"
#include "GL/glu.h"
#include <math.h>
#include <QDebug>

#include <engine.h>

#define SEA_SIZE 10
#define NEAR 3.0f
#define RELOAD_TIME_MSEC 750
#define MAP_COLLISION_OFFSET 0.1f
#define SHIP_COLLISION_OFFSET 0.1f
#define MISSILE_COLLISION_OFFSET 0.1f

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
    player1.draw(1, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(player2.xPos, 0, player2.zPos);
    glRotatef(player2.yAngle, 0, 1, 0);
    player2.draw(0, 0, 1);
    glPopMatrix();

    Missile* m;
    foreach(m, missilesList) {
        glPushMatrix();
        glTranslatef(m->x, 0.4, m->z);
        glRotatef(m->angle, 0, 1, 0);
        m->draw();
        glPopMatrix();
    }

    Point2D* p;
    foreach (p, player1.hitbox) {
        glColor3f(1,1,1);
        glBegin(GL_POINTS);
            glVertex3f(p->x, 0.4f, p->y);
        glEnd();
    }
}

void Engine::update() {
    player1_old = player1;
    player2_old = player2;

    if(!gamePause)
    {
        if(player1.forwardKeyPressed) player1.moveForward();
        if(player1.backwardKeyPressed) player1.moveBackward();
        if(player1.leftKeyPressed) player1.turnLeft();
        if(player1.rightdKeyPressed) player1.turnRight();
        if(player1.shotKeyPressed && !player1.reload) shotPlayer1();

        if(player2.forwardKeyPressed) player2.moveForward();
        if(player2.backwardKeyPressed) player2.moveBackward();
        if(player2.rightdKeyPressed) player2.turnRight();
        if(player2.leftKeyPressed) player2.turnLeft();
        if(player2.shotKeyPressed && !player2.reload) shotPlayer2();
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
    this->updateGL();
}

void Engine::resetGame() {
    player1.yAngle = 0.0;
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
    return (player->maxX > SEA_SIZE - MAP_COLLISION_OFFSET|| player->minX < -SEA_SIZE + MAP_COLLISION_OFFSET||
            player->maxZ > SEA_SIZE - MAP_COLLISION_OFFSET|| player->minZ < -SEA_SIZE + MAP_COLLISION_OFFSET)
            ? true : false;
}

bool Engine::checkCollisionMissileMap(Missile *missile) {
    return (missile->maxX > SEA_SIZE - MAP_COLLISION_OFFSET|| missile->minX < -SEA_SIZE + MAP_COLLISION_OFFSET||
            missile->maxZ > SEA_SIZE - MAP_COLLISION_OFFSET|| missile->minZ < -SEA_SIZE + MAP_COLLISION_OFFSET)
            ? true : false;
}

bool Engine::checkPlayersNear() {
    return (sqrt(pow((player1.xPos - player2.xPos), 2) + pow((player1.zPos - player2.zPos), 2)) < NEAR)
            ? true : false;
}

bool Engine::checkCollisionShipShip() {
    Point2D* p1;
    Point2D* p2;
    foreach (p1, player1.hitbox) {
        foreach (p2, player2.hitbox) {
            if(utils.getDistance(p1, p2) < SHIP_COLLISION_OFFSET) return true;
        }
    }

    return false;
}

bool Engine::checkCollisionMissileShip(Ship *player, Missile *missile) {
    if(missile->player == player) return false;

    Point2D* p;
    Point2D* m;
    foreach(p, player->hitbox) {
        foreach (m, missile->hitbox) {
            if(utils.getDistance(p, m) < MISSILE_COLLISION_OFFSET) {
                return true;
            }
        }
    }

    return false;
}

void Engine::updateMissiles() {
    Missile* m;
    foreach(m, missilesList) {
        if(m->isOutOfFuel() || checkCollisionMissileMap(m) ||
           checkCollisionMissileShip(&player1, m) || checkCollisionMissileShip(&player2, m)) {
            m->~Missile();
            missilesList.removeOne(m);
        }
    }
}

void Engine::shotPlayer1() {
    if(!player1.reload) {
        Missile *missile = new Missile(player1.xPos, player1.zPos, player1.yAngle, &player1);
        missilesList.append(missile);
        player1.reload = true;
        QTimer::singleShot(RELOAD_TIME_MSEC, this, SLOT(reloadDonePlayer1()));
    }
}

void Engine::shotPlayer2() {
    if(!player2.reload) {
        Missile *missile = new Missile(player2.xPos, player2.zPos, player2.yAngle, &player2);
        missilesList.append(missile);
        player2.reload = true;
        QTimer::singleShot(RELOAD_TIME_MSEC, this, SLOT(reloadDonePlayer2()));
    }
}

void Engine::reloadDonePlayer1() {
    player1.reload = false;
}

void Engine::reloadDonePlayer2() {
    player2.reload = false;
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
        player1.shotKeyPressed = true;
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
    case Qt::Key_Control:
        player2.shotKeyPressed = true;
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
    case Qt::Key_Space:
        player1.shotKeyPressed = false;
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
    case Qt::Key_Control:
        player2.shotKeyPressed = false;
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
