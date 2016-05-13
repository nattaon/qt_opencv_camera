#ifndef IMGPROC_H
#define IMGPROC_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImgProc
{
public:
    IplImage *process(IplImage *source, int type);
};

#endif // IMGPROC_H
