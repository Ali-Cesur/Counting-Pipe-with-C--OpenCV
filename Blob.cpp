/* OpenCV Find Number of Pipes */

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	
	// Read image
	Mat dst;
	Mat im = imread( "SDC10189.JPG", IMREAD_GRAYSCALE );
	namedWindow("Pipes",CV_WINDOW_NORMAL);
	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;
	equalizeHist( im, dst );
	dst.copyTo(im);
	Mat new_image = Mat::zeros( im.size(), im.type() );


//	new_image.copyTo(im);

	params.minThreshold = 20;
	params.maxThreshold = 230;
	int tast_min=(int)params.minThreshold;
	int tast_max=(int)params.maxThreshold;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 50;
	params.maxArea = 1600;
	int tast1=(int)params.minArea;
	int tast2=(int)params.maxArea;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1;
	//params.minCircularity = 0.6;

	// Filter by Convexity
	params.filterByConvexity = true;
	//params.minConvexity = 0.87;
	params.minConvexity = 0.5;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.06;
	//params.minInertiaRatio = 0.05;

	// Storage for blobs
	vector<KeyPoint> keypoints;

	vector<int> sparam;
	sparam.push_back(CV_IMWRITE_JPEG_QUALITY);
	sparam.push_back(50);

	createTrackbar("Threshold_Min", "Pipes", &tast_min, 100);
	createTrackbar("Threshold_Max", "Pipes", &tast_max, 255);
	createTrackbar("Min_Area", "Pipes", &tast1, 20000);
	createTrackbar("Max_Area", "Pipes", &tast2, 200000);

	while (true)
	{

		params.minArea=tast1;
		params.maxArea=tast2;
		params.minThreshold = tast_min;
		params.maxThreshold = tast_max;

		#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2
			// Set up detector with params
			SimpleBlobDetector detector(params);
			// Detect blobs
			detector.detect( im, keypoints);
		#else 
			// Set up detector with params
			Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);   
			// Detect blobs
			detector->detect( im, keypoints);
		#endif 

		// Draw detected blobs as red circles.
		// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
		// the size of the circle corresponds to the size of blob
			
		Mat im_with_keypoints;
		drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
		//the total no of blobs detected are:
		
		size_t x=keypoints.size();
		ostringstream str;
	    str << "Num of Pipes: " << x;
		putText(im_with_keypoints, str.str(), Point(2750,250), FONT_ITALIC, 2, Scalar(0,0,255), 3, 30, false );

		imshow("Pipes", im_with_keypoints );


		waitKey(100);
	}

	return 0;
}

