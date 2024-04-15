#include "samconsolemain.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

SAMEngine* engine {nullptr};

/**
 * @brief Global accessors.
*/
ControlBar *g_control_bar {nullptr};
ResultsStreamViewer *g_results_stream_viewer {nullptr};

int main(int argc, char **argv)
{
    /*
        Initialize the engine and register callbacks.
    */
    engine = new SAMEngine();
    engine->hook_scan_fire_callback(&scan_fire_callback);
    engine->hook_scan_complete_callback(&scan_complete_callback);
    engine->hook_new_file_callback(&new_file_callback);
    engine->hook_status_callback(&status_callback);

    QApplication sam_console_app(argc, argv);
    QCoreApplication::setOrganizationName(SAM_ORG_NAME);
    QCoreApplication::setApplicationName(SAM_CONSOLE_PROJECT_NAME);
    QCoreApplication::setApplicationVersion(SAM_CONSOLE_PROJECT_VERSION);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(sam_console_app);

    MainWindow w;
    g_control_bar = w.get_control_bar();
    g_results_stream_viewer = w.get_results_stream_viewer();
    w.resize(1440, 720);
    w.show();
    int result {sam_console_app.exec()};
    delete engine;
    return result;
}

void scan_fire_callback()
{
    g_results_stream_viewer->on_scan_fire();
}

void scan_complete_callback()
{
    g_results_stream_viewer->on_scan_complete();
}

int new_file_callback(const std::string& filename)
{
    return g_results_stream_viewer->on_new_file(filename);
}

void status_callback(const int& row_index, const float& prediction)
{
    g_results_stream_viewer->on_status(row_index, prediction);
}
