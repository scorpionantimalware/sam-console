#include "samconsolemain.hpp"

SAMEngine* engine {nullptr};

StatusViewer *status_viewer {nullptr};

int main(int argc, char **argv)
{
    engine = new SAMEngine();
    engine->hook_scan_fire_callback(&scan_fire_callback);
    engine->hook_scan_complete_callback(&scan_complete_callback);
    engine->hook_new_file_callback(&new_file_callback);
    engine->hook_status_callback(&status_callback);
    
    QApplication a(argc, argv);
    MainWindow w;
    status_viewer = w.get_status_viewer();
    w.resize(1440, 720);
    w.show();
    int result {a.exec()};
    delete engine;
    return result;
}

void scan_fire_callback()
{
    status_viewer->on_scan_fire();
}

void scan_complete_callback()
{
    status_viewer->on_scan_complete();
}

int new_file_callback(const std::string& filename)
{
    return status_viewer->on_new_file(filename);
}

void status_callback(const int& row_index, const float& prediction)
{
    status_viewer->on_status(row_index, prediction);
}
