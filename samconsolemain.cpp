/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * samconsolemain.cpp
 * 
 * Copyright (c) 2024-present Scorpion Anti-malware (see AUTHORS.md).
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include "samconsolemain.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/**
 * @brief Global accessors.
*/
ControlBar *g_control_bar {nullptr};
StatusBuiltinTerminal *g_status_builtin_terminal {nullptr};
ResultsStreamViewer *g_results_stream_viewer {nullptr};

int main(int argc, char **argv)
{
    // Make sure the MACRO has a valid directory path.
    if(!fs::exists(SAM_CONSOLE_ROOTDIR) || 
       !fs::is_directory(SAM_CONSOLE_ROOTDIR) || 
       ((fs::status(SAM_CONSOLE_ROOTDIR).permissions() & fs::perms::owner_read) == fs::perms::none)) {
        std::cerr << SAM_CONSOLE_ROOTDIR << " does not exist" << std::endl;
    }

    /*
        Initialize the engine and register callbacks.
    */
    sam_engine::hook_scan_fire_callback(&sam_callbacks::scan_fire_callback);
    sam_engine::hook_scan_complete_callback(&sam_callbacks::scan_complete_callback);
    sam_engine::hook_add_new_file_callback(&sam_callbacks::add_new_file_callback);
    sam_engine::hook_set_status_for_file_callback(&sam_callbacks::set_status_for_file_callback);
    sam_engine::hook_engine_state_change_callback(&sam_callbacks::engine_state_change_callback);
    sam_engine::hook_update_builtin_status_terminal_callback(&sam_callbacks::update_builtin_status_terminal_callback);

    QApplication sam_console_app(argc, argv);
    QCoreApplication::setOrganizationName(SAM_ORG_NAME);
    QCoreApplication::setApplicationName(SAM_CONSOLE_PROJECT_NAME);
    QCoreApplication::setApplicationVersion(SAM_CONSOLE_PROJECT_VERSION);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(sam_console_app);

    // Set the application style to Fusion (Under consideration)
    // sam_console_app.setStyle("fusion");
    // QPalette darkPalette;
    // darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    // darkPalette.setColor(QPalette::WindowText, Qt::white);
    // darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    // darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    // darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    // darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    // darkPalette.setColor(QPalette::Text, Qt::white);
    // darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    // darkPalette.setColor(QPalette::ButtonText, Qt::white);
    // darkPalette.setColor(QPalette::BrightText, Qt::red);
    // darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    // darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    // darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    // sam_console_app.setPalette(darkPalette);

    MainWindow w;
    g_control_bar = w.get_control_bar();
    g_status_builtin_terminal = w.get_status_builtin_terminal();
    g_results_stream_viewer = w.get_results_stream_viewer();
    w.resize(1440, 720);
    w.show();
    return sam_console_app.exec();
}

namespace sam_callbacks
{
    void scan_fire_callback()
    {
        g_results_stream_viewer->on_scan_fire();
    }

    void scan_complete_callback()
    {
        g_results_stream_viewer->on_scan_complete();
    }

    int add_new_file_callback(const std::string& filename)
    {
        return g_results_stream_viewer->on_new_file(filename);
    }

    void set_status_for_file_callback(const int& row_index, const float& prediction)
    {
        g_results_stream_viewer->on_status(row_index, prediction);
    }

    void engine_state_change_callback(const sam_engine::SAMEngineState::State& state)
    {
        g_control_bar->update_state(state);
    }

    void update_builtin_status_terminal_callback(const std::string& status, const sam_engine::SAMEngineStatusMessage& message_type)
    {
        g_status_builtin_terminal->append_message(status, message_type);
    }
} // namespace sam_callbacks

