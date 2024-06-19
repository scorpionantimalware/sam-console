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

#include "mainwindow.hpp"

#include "homepage.hpp"
#include "fimpage.hpp"

namespace fs = std::filesystem;

sam_engine::SAMEngine *engine {nullptr};

/**
 * @brief Global accessors.
*/
HomePage *g_home_page {nullptr};
FIMPage *g_fim_page {nullptr};

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
    sam_engine::hook_add_new_file_callback(&sam_callbacks::add_new_file_callback);
    sam_engine::hook_set_result_for_file_callback(&sam_callbacks::set_result_for_file_callback);
    sam_engine::hook_scanner_state_change_callback(&sam_callbacks::scanner_state_change_callback);
    sam_engine::hook_update_builtin_status_terminal_callback(&sam_callbacks::update_builtin_status_terminal_callback);

    // Initialize the Engine.
    engine = new sam_engine::SAMEngine();

    // Run the engine.
    engine->engine_main();

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

    g_home_page = w.get_home_page_p();
    g_fim_page = w.get_fim_page_p();
    
    w.resize(1440, 720);
    w.show();

    int ret {sam_console_app.exec()};

    // Request engine termination
    engine->fulfill_engine_termination_request();

    // Clean up the engine.
    delete engine;

    return ret;
}

namespace sam_callbacks {
    int add_new_file_callback(const std::string& filename)
    {
        return g_home_page->get_results_stream_viewer_p()->append_new_entry(filename);
    }

    void set_result_for_file_callback(const int& row_index, const float& prediction)
    {
        g_home_page->get_results_stream_viewer_p()->set_result_for_entry(row_index, prediction);
    }

    void scanner_state_change_callback([[maybe_unused]] const sam_engine::SAMScanner::State& state)
    {

    }

    void update_builtin_status_terminal_callback(const std::string& status, const sam_engine::SAMEngine::StatusMessageType& message_type)
    {
        g_home_page->get_status_builtin_terminal_p()->append_message(status, message_type);
    }
} // namespace sam_callbacks

