#include <QApplication>
#include "Webcam.h"
#include "stdio.h"

int main(int argc, char **args)
{
    QApplication app(argc, args);

    //int dev = 0; // default device
    //int fps = 25; // 25 frames per second

    WebCam *view = new WebCam();
    view->show();


    return app.exec();
}
