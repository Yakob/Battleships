#ifndef ENGINE_H
#define ENGINE_H

#include <QGLWidget>
#include <QColor>

#include <ship.h>

class Engine : public QGLWidget
{
    Q_OBJECT

public:
    Engine();
    ~Engine();

public slots:
    void update();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QTimer *timer;
    Utils utils;
    int xAngle;
    int yAngle;
    float scale;
    Ship player1;
    Ship player2;
    Ship player1_old;
    Ship player2_old;
    bool gamePause;
    bool playersMovment;

    void resetGame();
    void drawSea(int size);
    void turnLeft(Ship *player);
    void turnRight(Ship *player);
    void moveForward(Ship *player);
    void moveBackward(Ship *player);

    bool checkCollisionShipMap(Ship *player);
    bool checkPlayersNear();
    bool checkCollisionShipShip();
};

#endif // ENGINE_H
