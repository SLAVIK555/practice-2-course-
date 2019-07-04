#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

Mat edges;
//Mat src_gray;
int thresh = 100;
RNG rng(12345);


void thresh_callback(int, void* );


int main( int argc, char** argv )
{
    /// Load source image
    ///CommandLineParser parser( argc, argv, "{@input | ../data/stuff.jpg | input image}" );
    /*Mat */
	/*Mat src;
	src = imread( "input.jpg" );

    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        //cout << "usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }*/
	VideoCapture cap( "input7.webm" );
	if (!cap.isOpened())
	{
		return -1;
	}

	Mat source;
	//Mat edges;
	//namedWindow("edges", 1);

	while(1){
		Mat frame;
		bool bSuccess = cap.read(frame);
		if (!bSuccess){
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		imshow("edges", frame);

		cap>>frame;

		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
		thresh_callback( 0, 0 );

		if(waitKey(30) >= 0){
			break;
		}
	}
}

void thresh_callback(int, void* )
{
    /// Detect edges using canny
    Mat canny_output;
    Canny( edges, canny_output, thresh, thresh*2, 3 );//src_gray==edges
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
/*    for( size_t i = 0; i < contours.size(); i++ )
    {
        mc[i] = Point2f( static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)),
                         static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)) );
        //cout << "mc[" << i << "]=" << mc[i] << endl;
    }*/

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

	/*

	*/
}




/*


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
*/