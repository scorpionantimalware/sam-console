/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * mainwindow.cpp
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

#include "mainwindow.hpp"

#include <iostream>
#include <QTimer>

#define SPLASH_SCREEN_DELAY 2000

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), splash_screen(nullptr), main_layout(nullptr), control_bar(nullptr), status_builtin_terminal(nullptr), results_stream_viewer(nullptr), scan_areas_controller(nullptr) {
    // Initialize the main layout
    MainWindow::main_layout = new QVBoxLayout(this);
    MainWindow::main_layout->setSpacing(20);

    // TODO: This splash screen works fine but it crashes when pressing the 
    // scan button. I will need to investigate this further.

    // MainWindow::splash_screen = new SAMConsoleSplash();

    // Add splash screen to the main layout
    // MainWindow::main_layout->addWidget(MainWindow::splash_screen);

    // Use QTimer to remove splash screen and show main items after a delay
    // QTimer::singleShot(SPLASH_SCREEN_DELAY, this, &MainWindow::show_main_ui);

    MainWindow::show_main_ui();
}

MainWindow::~MainWindow()
{
    if (MainWindow::results_stream_viewer)
    {
        delete MainWindow::results_stream_viewer;
        MainWindow::results_stream_viewer = nullptr;
    }

    if (MainWindow::control_bar)
    {
        delete MainWindow::control_bar;
        MainWindow::control_bar = nullptr;
    }

    if (MainWindow::scan_areas_controller)
    {
        delete MainWindow::scan_areas_controller;
        MainWindow::scan_areas_controller = nullptr;
    }

    if (MainWindow::main_layout)
    {
        delete MainWindow::main_layout;
        MainWindow::main_layout = nullptr;
    }
}

void MainWindow::show_main_ui() {
    // Remove splash screen
    MainWindow::main_layout->removeWidget(MainWindow::splash_screen);

    // Delete the splash screen
    if (MainWindow::splash_screen)
    {
        delete MainWindow::splash_screen;
        MainWindow::splash_screen = nullptr;
    }

    // Initialize main items
    MainWindow::control_bar = new ControlBar();
    MainWindow::status_builtin_terminal = new StatusBuiltinTerminal();
    MainWindow::results_stream_viewer = new ResultsStreamViewer();

    // Add main items to the layout
    MainWindow::main_layout->addWidget(MainWindow::control_bar, 1); // The control bar will take up 1/8 of the space.
    MainWindow::main_layout->addWidget(MainWindow::status_builtin_terminal, 2); // The terminal will take up 2/8 of the space.
    MainWindow::main_layout->addWidget(MainWindow::results_stream_viewer, 5); // The viewer will take up 5/8 of the space.

    // Connect signals and slots
    connect(MainWindow::control_bar, &ControlBar::scan_button_clicked, MainWindow::results_stream_viewer, &ResultsStreamViewer::on_scan_button_clicked);
    connect(MainWindow::control_bar, &ControlBar::scan_areas_controller_button_clicked, this, &MainWindow::on_scan_areas_controller_button_clicked);
}

ControlBar* MainWindow::get_control_bar()
{
    return MainWindow::control_bar;
}

ResultsStreamViewer* MainWindow::get_results_stream_viewer()
{
    return MainWindow::results_stream_viewer;
}

void MainWindow::on_scan_areas_controller_button_clicked()
{
    std::cout << "Scan areas controller clicked" << std::endl;

    if (!MainWindow::scan_areas_controller)
    {
        // TODO: Make the controller block the main window.
        MainWindow::scan_areas_controller = new ScanAreasController();
    }
    
    MainWindow::scan_areas_controller->show();
}
