#include <opencv2/opencv.hpp>
#include <cmath>

#include "FrameBuffer.h"

using namespace std;

int main(int argc, char** argv) {
	int cameraId;

	std::cout << "Enter camera id: ";
	while (!(std::cin >> cameraId)) {  // Check if the input is an integer
		std::cout << "Invalid input! Please enter an integer: ";
		std::cin.clear();  // Clear the error state
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
	}

    // Open the default camera (usually the first camera)
    cv::VideoCapture cap(cameraId);

    int frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cout << frameWidth << "x" << frameHeight << endl;

    // Check if we succeeded in opening the webcam
    if (!cap.isOpened()) {
        cerr << "Error: Could not open the webcam." << endl;
        return -1;
    }

    int rate = floor(frameHeight / 8);

    FrameBuffer frame_buffer(rate, frameHeight, frameWidth);

    // Create a window to display the video
    cv::namedWindow("Webcam", cv::WINDOW_FULLSCREEN);

    // Loop to capture frames and display them
    while (true) {
        cv::Mat frame;

        // Capture a new frame
        cap >> frame;

        // Check if the frame is empty (end of video stream)
        if (frame.empty()) {
            cerr << "Error: Empty frame captured." << endl;
            break;
        }

        frame_buffer.addFrame(frame);
        cv::Mat out_frame = frame_buffer.getFrame();

        if (cameraId == 1) {
			cv::Mat out;
			cv::resize(out_frame, out_frame, cv::Size(), 2, 2, cv::INTER_CUBIC);
        }

        // Display the frame
        cv::imshow("Webcam", out_frame);

        // Wait for the 'Esc' key to be pressed to exit
        char key = (char)cv::waitKey(1);
        if (key == 27) break;
    }

    cap.release();
    cv::destroyWindow("Webcam");

    return 0;
}
