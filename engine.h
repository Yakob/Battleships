#ifndef ENGINE_H
#define ENGINE_H

#include <QGLWidget>
#include <QColor>

#include <ship.h>
#include <missile.h>

class Engine : public QGLWidget
{
    Q_OBJECT

public:
    Engine();
    ~Engine();
    QList<Missile*> missilesList;

public slots:
    void update();
    void reloadDonePlayer1();
    void reloadDonePlayer2();

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
    QString pauseText;
    QString newGameText;

    void resetGame();
    void drawSea(int size);
    void shotPlayer1();
    void shotPlayer2();
    QString getHitpoints(Ship* player);
    QString checkForWinner();

    bool checkCollisionShipMap(Ship *player);
    bool checkCollisionMissileMap(Missile* missile);
    bool checkPlayersNear();
    bool checkCollisionShipShip();
    bool checkCollisionMissileShip(Ship* player, Missile* missile);
    void updateMissiles();
};

#endif // ENGINE_H
