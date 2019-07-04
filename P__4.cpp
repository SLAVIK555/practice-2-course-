/*#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace cv;
using namespace std;

Mat src;
Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

/** @function main 
int main(int argc, char* argv[])//int main(int argc, char** argv)
{
  /// Load source image and convert it to gray
	src = imread("D:\Visual Studio 2008\Projects\Project___4\Input.jpg");
	if(!src.data){
		return -1;
	}
  /// Convert image to gray and blur it
  /*
  cvtColor(original, gray, CV_BGR2GRAY)
  ////////////////
  if(original.empty())
    break;
else if(original.channels()>1)
    cvtColor(original, gray, CV_BGR2GRAY);
else gray = original;
*/
 // cvtColor(src, src_gray, CV_BGR2GRAY);
  ////////////////
  /*if(src.empty())
  {
	  //continue;
	  //return(0);
	  //return;//break;
  }
  else*/
  /*if(src.channels()>1)
	  cvtColor(src, src_gray, CV_BGR2GRAY);
  else src_gray = src;*/
/*
  blur(src_gray, src_gray, Size(3,3));

  /// Create Window
  char* source_window = "Source";
  namedWindow(source_window, CV_WINDOW_AUTOSIZE);
  imshow(source_window, src);

  createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
  thresh_callback(0, 0);

  waitKey(0);
  return(0);
}

// @function thresh_callback 
void thresh_callback(int, void*)
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny(src_gray, canny_output, thresh, thresh*2, 3);
  /// Find contours
  findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  /// Get the moments
  vector<Moments> mu(contours.size());
  for(int i = 0; i < contours.size(); i++)
    {
		mu[i] = moments( contours[i], false );
	}

  ///  Get the mass centers:
  vector<Point2f> mc( contours.size() );
  for( int i = 0; i < contours.size(); i++ )
    {
		mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
	}

  /// Draw contours
  Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
  for(int i = 0; i< contours.size(); i++)
     {
       Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
       drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
       circle(drawing, mc[i], 4, color, -1, 8, 0);
     }

  /// Show in a window
  namedWindow("Contours", CV_WINDOW_AUTOSIZE);
  imshow("Contours", drawing);

  /// Calculate the area with the moments 00 and compare with the result of the OpenCV function
  printf("\t Info: Area and Contour Length \n");
  for(int i = 0; i< contours.size(); i++)
     {
       printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
       Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
       drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
       circle(drawing, mc[i], 4, color, -1, 8, 0);
     }
}
*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

Mat src_gray;
int thresh = 100;
RNG rng(12345);


void thresh_callback(int, void* );


int main( int argc, char** argv )
{
    /// Load source image
	Mat src;
	src = imread( "input.jpg" );

    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        //cout << "usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );

    const int max_thresh = 255;
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

    waitKey();
    return 0;
}


void thresh_callback(int, void* )
{
    /// Detect edges using canny
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    vector<vector<Point> > contours;
    findContours( canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );

    /// Get the moments
    vector<Moments> mu(contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        mu[i] = moments( contours[i] );
    }

    ///  Get the mass centers
    vector<Point2f> mc( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        mc[i] = Point2f( static_cast<float>(mu[i].m10 / (mu[i].m00)),
                         static_cast<float>(mu[i].m01 / (mu[i].m00)) );
        cout << "mc[" << i << "]=" << mc[i] << endl;
    }

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2 );
        circle( drawing, mc[i], 4, color, -1 );
    }

    /// Show in a window
    imshow( "Contours", drawing );

    /*/// Calculate the area with the moments 00 and compare with the result of the OpenCV function
    cout << "\t Info: Area and Contour Length \n";
    for( size_t i = 0; i < contours.size(); i++ )
    {
        cout << " * Contour[" << i << "] - Area (M_00) = " << std::fixed << std::setprecision(2) << mu[i].m00
             << " - Area OpenCV: " << contourArea(contours[i]) << " - Length: " << arcLength( contours[i], true ) << endl;
    }*/
}
