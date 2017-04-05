#include "window.h"

#include <iostream>
#include <gtkmm.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "ch.undef.gtkmmOpenCvSample");

    window_t win;

    return app->run(win);
}
