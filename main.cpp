#include <QApplication>
#include <QDesktopWidget>

#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QGLFormat::hasOpenGL()) {
        qDebug("Your system does not seem to support OpenGL. Cannot run this example.");
        return EXIT_FAILURE;
    }

    Engine e;
    static int desktopWitdh = QApplication::desktop()->width();
    static int desktopHeight = QApplication::desktop()->height();
    static int appWidth = 800;
    static int appHeight = 600;
    e.setWindowTitle("Battleships by Jakub Kapuscik");

    if(appWidth > desktopWitdh || appHeight > desktopHeight)
    {
        return 0;
    }
    else if (appWidth == desktopWitdh && appHeight == desktopHeight) {
        e.showFullScreen();
    }
    else
    {
        e.setFixedSize(appWidth, appHeight);
        e.setGeometry((desktopWitdh - appWidth)/2,
                      (desktopHeight - appHeight)/2,
                      appWidth, appHeight);
        e.show();
    }

    return app.exec();
}
