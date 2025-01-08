#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(size_t rate, size_t height, size_t width)
	: rate(rate), height(height), width(width), pos(0) {

	in_buffer = new cv::Mat[rate];  // Allocate memory for the buffer

	// Initialize each matrix in the buffer with zeros
	for (size_t i = 0; i < rate; ++i) {
		in_buffer[i] = cv::Mat::zeros(height, width, CV_8UC3);
	}
}

FrameBuffer::~FrameBuffer() {
	delete[] in_buffer;
}

void FrameBuffer::addFrame(const cv::Mat& frame) {
	in_buffer[pos % rate] = frame;
	//pos += 1;
}

cv::Mat FrameBuffer::getFrame() {
	cv::Mat out_frame; // Initialize an empty matrix
	int mod = floor(height / rate);

	for (int i = 0; i < rate; ++i) {
		int index = (pos - i + rate) % rate; // Handle circular indexing to ensure non-negative indices
		cv::Mat slice = in_buffer[index].rowRange(i * mod, (i + 1) * mod);

		if (out_frame.empty()) {
			// If out_frame is empty, set it to the first slice
			out_frame = slice.clone();
		}
		else {
			// Append the slice vertically
			cv::vconcat(out_frame, slice, out_frame);
		}
	}
	pos += 1; // Update the position
	return out_frame;
}
