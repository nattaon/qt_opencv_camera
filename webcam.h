#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include <QTime>
#include <QVBoxLayout>
#include <QPushButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "imgproc.h"


class WebCam: public QWidget
{
    Q_OBJECT

public:
    WebCam(QWidget *parent=0);
    ~WebCam();
    QVBoxLayout *layout;
    QPushButton *button_start;
    QPushButton *button_stop;

private slots:
    void startCapture();
    void stopCapture();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    CvCapture* capture;
    int timerId;
    int frameRate; // input frame rate
    QPixmap pixmap;
    int nframes; // used to calculate actual frame rate
    QTime time; // used to calculate actual frame rate
    // convert image format
    QImage IplImage2QImage(const IplImage *iplImage);

    ImgProc* imgProc;
    int demoType;
};

#endif // WEBCAM_H
