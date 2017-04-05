#ifndef CVDRAWER_H
#define CVDRAWER_H

#include <gtkmm.h>
#include <opencv2/opencv.hpp>

class opencv_view_t : public Gtk::DrawingArea {
public:

    enum draw_mode_e {
        SCALE,
        CENTER,
        CENTER_FIT,
    };

    opencv_view_t();

    void set_cv_mat(const cv::Mat& mat);

    // Widget interface
protected:
    bool on_draw(const::Cairo::RefPtr<Cairo::Context> &cr) override;
    void get_preferred_width_vfunc(int &minimum_width, int &natural_width) const override;
    void get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const override;
    void get_preferred_height_vfunc(int &minimum_height, int &natural_height) const override;
    void get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const override;

private:
    cv::Mat mat;
    draw_mode_e drawMode;
};

#endif // CVDRAWER_H
