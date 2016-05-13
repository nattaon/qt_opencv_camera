#include "imgproc.h"
#include <opencv2/imgproc/imgproc.hpp>

IplImage *ImgProc::process(IplImage *source, int type)
{
    static IplImage *target = NULL;
    if (target)
        cvReleaseImage(&target);
    target = cvCreateImage( cvSize(source->width, source->height),
                            source->depth, source->nChannels);

    switch(type)
    {
        case 0: // do nothing
            return source;
        case 1: // demo fast algo: fast smoothing
            //cvSmooth(source, target, CV_GAUSSIAN, 5);
            //return target;
			return source;
        case 2: // demo slow algo: filter with large kernel
        {
            //int size = 100;
            //CvMat *kernel = cvCreateMat(size, size, CV_32FC1);
            //cvSet(kernel, cvScalar(1.0 / size / size));
            //cvFilter2D(source, target, kernel);
            //cvReleaseMat(&kernel);
            // Filter target is too blurred for display.
            // Display the following for demo purpose.
            //cvSmooth(source, target, CV_GAUSSIAN, 5);
            //return target;
			return source;
        }
        default: // do nothing
            return source;
    }
}
