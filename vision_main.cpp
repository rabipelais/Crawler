#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>


int main(int argc, char *argv[])
{
  int height,width,step,channels;
  uchar *data;
  int i,j,k;


  if(argc<2){
    printf("Usage: vision <image-file-name>\n\7");
    exit(0);
  }

  // load an image  
  CvMat* img = cvLoadImageM(argv[1]);
  if(!img){
    printf("Could not load image file: %s\n",argv[1]);
    exit(0);
  }

  
  // get the image data
  height    = img->height;
  width     = img->width;
  printf("Processing a %dx%d image\n",height,width); 
  
  // create the camera matrix with the intrinsic parameters
  //35.8 mm / 5616 px = 0.00637464387464387464, 23.9 mm / 3744 px = 0.00638354700854700855
  // focal length = 15 mm, resolution = 5616 x 3744
  double cameraParameters[] = {2353.07262, 0.0, 2808, 0.0, 2349.79079, 1872, 0.0, 0.0, 1.0};
  CvMat cameraMat = cvMat(3,3,CV_32FC1,cameraParameters);

  // create the distortion array, assume no tangential distortion,
  // and lens:
  double distortionParameters[] = {-0.18957, 0.03732, 0.0, 0.0, -0.003367};
  double identityDistortionParameters[] = {0.0, 0.0, 0.0, 0.0, 0.0};
  CvMat distortionMat = cvMat(1,5,CV_32FC1, identityDistortionParameters);

  // creat output image
  CvMat* output = cvCreateMat(height, width, CV_8UC3);
/*  // create a window
  cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
  cvMoveWindow("mainWin", 100, 100);


  // show the image
  cvShowImage("mainWin", img );

  // wait for a key
  cvWaitKey(0);
*/

  // undistort image
  cvUndistort2(img, output, &cameraMat, &distortionMat);
  
  if(!cvSaveImage("output.jpg",output)) {
      printf("Could not save: %s\n","output.jpg");
  } else {
      printf("Saved image!\n");
  }
  // release the image
  cvReleaseMat(&img);
  cvReleaseMat(&output);
  //cvReleaseMat(distortionMat);
  //cvReleaseMat(cameraMat);
  
  return 0;
}
