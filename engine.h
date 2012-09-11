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
    int xAngle;
    int yAngle;
    float scale;
    Ship player1;
    Ship player2;
    bool gamePause;

    void resetGame();
    void drawSea(int size);
    void turnLeft(Ship *player);
    void turnRight(Ship *player);
    void moveForward(Ship *player);
    void moveBackward(Ship *player);

    void checkCollisionShipMap(Ship *player);
};

#endif // ENGINE_H
