#ifndef FRAME_BUFFER_CLASS_H
#define FRAME_BUFFER_CLASS_H

#include <opencv2/opencv.hpp>
#include <cmath>

class FrameBuffer {
public:
    cv::Mat* in_buffer;
    size_t rate;
    size_t height;
    size_t width;
    int pos;

    FrameBuffer(size_t rate, size_t height, size_t width);
    ~FrameBuffer();

    void addFrame(const cv::Mat& frame);
    cv::Mat getFrame();
};


#endif
