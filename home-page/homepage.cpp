/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * homepage.cpp
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

#include "homepage.hpp"

#include <iostream>
#include <QTimer>

#include "samconsolemain.hpp"

HomePage::HomePage(QWidget *parent) : QWidget(parent), main_layout(nullptr), control_bar(nullptr), status_builtin_terminal(nullptr), results_stream_viewer(nullptr), scan_areas_controller(nullptr) {
    // Initialize the main layout
    HomePage::main_layout = new QVBoxLayout(this);
    HomePage::main_layout->setSpacing(20);

    // Initialize main items
    HomePage::control_bar = new ControlBar();
    HomePage::status_builtin_terminal = new StatusBuiltinTerminal();
    HomePage::results_stream_viewer = new ResultsStreamViewer();

    // Add main items to the layout
    HomePage::main_layout->addWidget(HomePage::control_bar, 1); // The control bar will take up 1/8 of the space.
    HomePage::main_layout->addWidget(HomePage::status_builtin_terminal, 2); // The terminal will take up 2/8 of the space.
    HomePage::main_layout->addWidget(HomePage::results_stream_viewer, 5); // The viewer will take up 5/8 of the space.

    // Connect signals and slots
    connect(HomePage::control_bar, &ControlBar::scan_button_clicked, this, &HomePage::on_scan_button_clicked);
    connect(HomePage::control_bar, &ControlBar::stop_button_clicked, this, &HomePage::on_stop_button_clicked);
    connect(HomePage::control_bar, &ControlBar::pause_button_clicked, this, &HomePage::on_pause_button_clicked);
    connect(HomePage::control_bar, &ControlBar::scan_areas_controller_button_clicked, this, &HomePage::on_scan_areas_controller_button_clicked);
}

HomePage::~HomePage()
{
    if (HomePage::results_stream_viewer)
    {
        delete HomePage::results_stream_viewer;
        HomePage::results_stream_viewer = nullptr;
    }

    if (HomePage::control_bar)
    {
        delete HomePage::control_bar;
        HomePage::control_bar = nullptr;
    }

    if (HomePage::scan_areas_controller)
    {
        delete HomePage::scan_areas_controller;
        HomePage::scan_areas_controller = nullptr;
    }

    if (HomePage::main_layout)
    {
        delete HomePage::main_layout;
        HomePage::main_layout = nullptr;
    }
}

ControlBar* HomePage::get_control_bar_p() const {
    return HomePage::control_bar;
}

StatusBuiltinTerminal* HomePage::get_status_builtin_terminal_p() const {
    return HomePage::status_builtin_terminal;
}

ResultsStreamViewer* HomePage::get_results_stream_viewer_p() const {
    return HomePage::results_stream_viewer;
}

void HomePage::on_scan_button_clicked()
{
    std::cout << "Scanning..." << std::endl;
    engine->fulfill_start_scan_request();
}

void HomePage::on_stop_button_clicked()
{
    std::cout << "Stopping..." << std::endl;
    engine->fulfill_stop_scan_request();
}

void HomePage::on_pause_button_clicked()
{
    std::cout << "Pausing..." << std::endl;
    engine->fulfill_pause_scan_request();
}

void HomePage::on_scan_areas_controller_button_clicked()
{
    std::cout << "Scan areas controller clicked" << std::endl;

    if (!HomePage::scan_areas_controller)
    {
        // TODO: Make the controller block the main window.
        HomePage::scan_areas_controller = new ScanAreasController();
    }
    
    HomePage::scan_areas_controller->show();
}
