#include <highgui.h>
#include <iostream>
#include <stdio.h>
#include <cv.h>

using namespace std;
using namespace cv;
using namespace std;

int main() {

	cvNamedWindow(“Trash detecting camera", 1);
	// Capture images from any camera connected to the system
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);

	// Load the trained model
	CascadeClassifier trashDetector;
	trashDetector.load("src/obj1.xml");

	if (trashDetector.empty()) {
		printf("Empty model.");
		return 0;
	}

	char key;
	while (true) {

		// Get a frame from the camera
		Mat frame = cvQueryFrame(capture);

		std::vector<Rect> obj;

		// Detect obj
		brezelDetector.detectMultiScale(frame, obj, 1.1, 30,
				0 | CV_HAAR_SCALE_IMAGE, Size(200, 320));

		for (int i = 0; i < (int) obj.size(); i++) {
			Point pt1(obj[i].x, obj[i].y);
			Point pt2(obj[i].x + obj[i].width,
					obj[i].y + obj[i].width);

			// Draw a rectangle around the detected trash
			rectangle(frame, pt1, pt2, Scalar(0, 0, 255), 2);
			putText(frame, “trash", pt1, FONT_HERSHEY_PLAIN, 1.0,
					Scalar(255, 0, 0), 2.0);

		}

		// Show the transformed frame
		imshow("Trash detecting camera", frame);

		// Read keystrokes, exit after ESC pressed
		key = cvWaitKey(10);
		if (char(key) == 27) {
			break;
		}
	}

	return 0;
}