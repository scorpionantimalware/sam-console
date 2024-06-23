/**********************************************************************************/
/*                                                                                */
/* samconsolemain.cpp                                                             */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware Console is a free Open Source Qt-powered frontend     */
/*    framework for SAM Engine.                                                   */
/*                                                                                */
/*    Copyright (c) 2024-present  (see AUTHORS.md).                               */
/*                                                                                */
/*    This program is free software: you can redistribute it and/or modify        */
/*    it under the terms of the GNU General Public License as published by        */
/*    the Free Software Foundation, either version 3 of the License, or           */
/*    (at your option) any later version.                                         */
/*                                                                                */
/*    This program is distributed in the hope that it will be useful,             */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of              */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               */
/*    GNU General Public License for more details.                                */
/*                                                                                */
/*    You should have received a copy of the GNU General Public License           */
/*    along with this program.  If not, see <https://www.gnu.org/licenses/>.      */
/*                                                                                */
/**********************************************************************************/

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

int main(int argc, char **argv) {
    std::cout << "Scorpion Anti-malware Console  Copyright (C) 2024-present (see AUTHORS.md)\n"
    "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions; type `show c' for details.\n" << std::endl;

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
    sam_engine::hook_update_new_file_callback(&sam_callbacks::update_new_file_callback);
    sam_engine::hook_scanner_state_change_callback(&sam_callbacks::scanner_state_change_callback);
    sam_engine::hook_update_engine_status_callback(&sam_callbacks::update_engine_status_callback);

    sam_engine::hook_fim_new_event_callback(&sam_callbacks::fim_new_event_callback);
    sam_engine::hook_fim_update_event_callback(&sam_callbacks::fim_update_event_callback);

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

    // Start the FIM
    engine->fulfill_start_fim_request();

    int ret {sam_console_app.exec()};

    // Request engine termination
    engine->fulfill_engine_termination_request();

    // Clean up the engine.
    delete engine;
    engine = nullptr;

    return ret;
}

namespace sam_callbacks {
    int add_new_file_callback()
    {
        return g_home_page->get_scan_results_monitor_p()->append_new_entry();
    }

    void update_new_file_callback(const int& row_index, const int& col_index, const std::string& data_buffer, const float& status_prediction)
    {
        g_home_page->get_scan_results_monitor_p()->update_entry(row_index, col_index, data_buffer, status_prediction);
    }

    void scanner_state_change_callback([[maybe_unused]] const sam_engine::SAMScanner::State& scanner_state)
    {

    }

    void update_engine_status_callback(const std::string& status_message, const sam_engine::SAMEngine::StatusMessageType& type)
    {
        g_home_page->get_engine_status_monitor_p()->append_message(status_message, type);
    }

    void fim_new_event_callback()
    {
        g_fim_page->get_events_monitor_p()->append_new_entry();
    }

    void fim_update_event_callback(const int& row_index, const int& col_index, const std::string& data_buffer)
    {
        g_fim_page->get_events_monitor_p()->update_entry(row_index, col_index, data_buffer);
    }
} // namespace sam_callbacks

