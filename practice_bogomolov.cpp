#include "opencv/cxcore.hpp"
#include "opencv/cv.hpp"
#include "opencv/highgui.h"
#include<iostream>

using namespace cv;
using namespace std;

Mat src; 
Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void* );

int main( int argc, char** argv )
{
  // Load source image and convert it to gray
  src = imread( argv[1], 1 );

  // Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  // Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  // Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  // Get the moments
  vector<Moments> mu(contours.size() ); 
  for(  int i =  0;  i <  contours.size ();  i++ ) 
     {  mu [ i ]  =  moments ( contours [ i ],  false ); }

  // Get the mass centers:
  vector< Point2f>>  mc( contours.size() ); 
  for(  int i =  0;  i <  contours.size();  i++ ) 
     { mc[ i]  =  Point2f( mu[ i].m10/ mu[ i].m00 ,  mu[ i].m01/mu[i].m00 ); } 
}

