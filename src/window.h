#ifndef WINDOW_H
#define WINDOW_H

#include "opencv_view.h"
#include "gtkmm.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>
#include <mutex>

class window_t : public Gtk::Window {
public:
    window_t();
    ~window_t();

private:
    cv::VideoCapture cv_video_capture;
    cv::Mat frame_from_video_capture_thread;
    cv::Mat camMat;
    opencv_view_t cv_view;

    std::thread capture_thread;
    std::mutex capture_mutex;
    std::atomic_bool is_cam_closed;

    Glib::Dispatcher signal_new_frame_ready;

    void set_frame(const cv::Mat& frame) {
        std::lock_guard<std::mutex> guard(capture_mutex);
        frame_from_video_capture_thread = frame.clone();
        signal_new_frame_ready.emit();
    };

    cv::Mat get_frame() {
        std::lock_guard<std::mutex> guard(capture_mutex);
        return frame_from_video_capture_thread.clone();
    }
};

#endif // WINDOW_H
