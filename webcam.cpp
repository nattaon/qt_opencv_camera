#include <QtGui>
#include <QtDebug>
#include "Webcam.h"
//#include "build/ui_webcam.h"


WebCam::WebCam(QWidget *parent) : QWidget(parent)
{

    setFixedSize(640, 480);
	

    imgProc = new ImgProc;

    layout = new QVBoxLayout;

    button_start = new QPushButton;
    button_start->setObjectName(QStringLiteral("button_start"));
    button_start->setMaximumSize(QSize(50, 40));
    button_start->setText("start");


    button_stop = new QPushButton;
    button_stop->setObjectName(QStringLiteral("button_stop"));
    button_stop->setMaximumSize(QSize(50, 40));
    button_stop->setText("stop");





    connect(button_start, SIGNAL(pressed()), this, SLOT(startCapture()));
    connect(button_stop, SIGNAL(pressed()), this, SLOT(stopCapture()));


    layout->addWidget(button_start);
    layout->addWidget(button_stop);

    setLayout(layout);

}

WebCam::~WebCam()
{
    cvReleaseCapture(&capture);
    delete imgProc;
}
void WebCam::showEvent(QShowEvent *event)
{
	qDebug() << "showEvent";

}
void WebCam::hideEvent(QHideEvent *event)
{
	qDebug() << "hideEvent";

}

void WebCam::timerEvent(QTimerEvent *event)
{
	//qDebug() << "timerEvent";

    if (event->timerId() == timerId)
    {
        IplImage *frame = cvQueryFrame(capture);
        IplImage *target = imgProc->process(frame, demoType);

        QImage image = IplImage2QImage(frame); // convert
        pixmap = QPixmap::fromImage(image); // convert
        repaint(); // immediate repaint
        if (++nframes == 50)
        {
            qDebug("frame rate: %f", // actual frame rate
            (float) nframes * 1000 / time.elapsed());
            nframes = 0;
            time.restart();
        }
    }
    else
        QWidget::timerEvent(event);
}

void WebCam::paintEvent(QPaintEvent *event)
{
	//qDebug() << "paintEvent";

    QRectF rect = QRectF(QPoint(), size());
    QPainter painter(this);
    painter.drawPixmap(rect, pixmap, rect);
}

// Convert OpenCV's IplImage to QImage.
QImage WebCam::IplImage2QImage(const IplImage *iplImage)
{
    int height = iplImage->height;
    int width = iplImage->width;
    if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3) // colour image
    {
        const uchar *qImageBuffer = (const uchar*) iplImage->imageData;
        QImage img(qImageBuffer, width, height,
        QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1) // gray image
    {
        const uchar *qImageBuffer = (const uchar*) iplImage->imageData;
        QImage img(qImageBuffer, width, height,
        QImage::Format_Indexed8);
        QVector<QRgb> colorTable; // set up colour table
        for (int i = 0; i < 256; i++)
            colorTable.append(qRgb(i, i, i));
        img.setColorTable(colorTable);
        return img;
    }
    else
    {
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}

void WebCam::startCapture()
{
	qDebug() << "press start";

	capture = cvCaptureFromCAM(0);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);



	nframes = 0; // init
	timerId = startTimer(1000 / frameRate); // in msec
	time.start(); // start time


}
void WebCam::stopCapture()
{
	qDebug() << "press stop";
    
    killTimer(timerId);
	pixmap.fill(Qt::white);
	repaint(); // immediate repaint

	cvReleaseCapture(&capture);

}


