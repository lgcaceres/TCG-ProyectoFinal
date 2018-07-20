#include <cv.h>
#include <highgui.h>

int main()
{
IplImage *im = cvLoadImage("eagle.jpg",CV_WINDOW_AUTOSIZE);
cvNamedWindow("image",CV_WINDOW_NORMAL);
cvShowImage("image2", im);
cvWaitKey(0);
cvReleaseImage(&im);
cvDestroyAllWindows();
}