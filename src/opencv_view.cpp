#include "opencv_view.h"

opencv_view_t::opencv_view_t() : drawMode(CENTER_FIT) {

}

void opencv_view_t::set_cv_mat(const cv::Mat &m) {
    mat = m;
    queue_draw();
}

bool opencv_view_t::on_draw(const::Cairo::RefPtr<Cairo::Context> &cr) {

    auto w = get_allocated_width();
    auto h = get_allocated_height();

    cr->save();
    cr->set_source_rgb(0, 0, 0);
    cr->paint();
    cr->restore();

    if (mat.empty()) {
        auto layout = create_pango_layout("No input set");

        int text_w, text_h;
        layout->get_pixel_size(text_w, text_h);

        cr->set_source_rgb(.8, .8, .8);
        cr->move_to((w - text_w) / 2, (h - text_h) / 2);
        layout->show_in_cairo_context(cr);

    } else {
        cv::Mat mat1;
        cv::cvtColor(mat, mat1, CV_BGR2RGB);

        double x = 0;
        double y = 0;
        double scaleX = 1;
        double scaleY = 1;

        switch (drawMode) {
            case SCALE:
                scaleX = w / double(mat1.cols);
                scaleY = h / double(mat1.rows);
                break;
            case CENTER:
                x = (w / 2) - mat1.cols / 2;
                y = (h / 2) - mat1.rows / 2;
                break;
            case opencv_view_t::CENTER_FIT:
                scaleX = scaleY = MIN(w / double(mat1.cols), h / double(mat1.rows));

                x = (w / 2) - (mat1.cols * scaleX) / 2;
                y = (h / 2) - (mat1.rows * scaleY) / 2;

                break;
        }

        cr->translate(x, y);
        cr->scale(scaleX, scaleY);

        Gdk::Cairo::set_source_pixbuf(cr, Gdk::Pixbuf::create_from_data(mat1.data, Gdk::COLORSPACE_RGB, false, 8, mat1.cols, mat1.rows, mat1.step));

        cr->paint();
    }

    return true;
}

void opencv_view_t::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const {
    minimum_width = 0;
    natural_width = mat.cols;
}

void opencv_view_t::get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const {
    double ratio = mat.cols / double(mat.rows);
    natural_height = width * ratio;
    minimum_height = (drawMode == SCALE) ? 0 : natural_height;
}

void opencv_view_t::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const {
    minimum_height = 0;
    natural_height = mat.rows;
}

void opencv_view_t::get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const {
    double ratio = mat.rows / double(mat.cols);
    natural_width = height * ratio;
    minimum_width = (drawMode == SCALE) ? 0 : natural_width;
}
