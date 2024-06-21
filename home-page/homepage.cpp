/**********************************************************************************/
/*                                                                                */
/* homepage.cpp                                                                   */
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


#include "homepage.hpp"

#include <iostream>
#include <QTimer>

#include "samconsolemain.hpp"

HomePage::HomePage(QWidget *parent) : QWidget(parent), main_layout(nullptr), control_bar(nullptr), engine_status_monitor(nullptr), scan_results_monitor(nullptr), scan_areas_controller(nullptr) {
    // Initialize the main layout
    HomePage::main_layout = new QVBoxLayout(this);
    HomePage::main_layout->setSpacing(20);

    // Initialize main items
    HomePage::control_bar = new ControlBar();
    HomePage::engine_status_monitor = new EngineStatusMonitor();
    HomePage::scan_results_monitor = new ScanResultsMonitor();

    // Add main items to the layout
    HomePage::main_layout->addWidget(HomePage::control_bar, 1); // The control bar will take up 1/8 of the space.
    HomePage::main_layout->addWidget(HomePage::engine_status_monitor, 2); // The terminal will take up 2/8 of the space.
    HomePage::main_layout->addWidget(HomePage::scan_results_monitor, 4); // The viewer will take up 5/8 of the space.

    // Connect signals and slots
    connect(HomePage::control_bar, &ControlBar::scan_button_clicked, this, &HomePage::on_scan_button_clicked);
    connect(HomePage::control_bar, &ControlBar::stop_button_clicked, this, &HomePage::on_stop_button_clicked);
    connect(HomePage::control_bar, &ControlBar::pause_button_clicked, this, &HomePage::on_pause_button_clicked);
    connect(HomePage::control_bar, &ControlBar::scan_areas_controller_button_clicked, this, &HomePage::on_scan_areas_controller_button_clicked);
}

HomePage::~HomePage()
{
    if (HomePage::scan_results_monitor)
    {
        delete HomePage::scan_results_monitor;
        HomePage::scan_results_monitor = nullptr;
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

EngineStatusMonitor* HomePage::get_engine_status_monitor_p() const {
    return HomePage::engine_status_monitor;
}

ScanResultsMonitor* HomePage::get_scan_results_monitor_p() const {
    return HomePage::scan_results_monitor;
}

void HomePage::on_scan_button_clicked()
{
    std::cout << "Scanning..." << std::endl;
    engine->fulfill_start_scan_request();
}

void HomePage::on_stop_button_clicked()
{
    std::cout << "Stopping..." << std::endl;
}

void HomePage::on_pause_button_clicked()
{
    std::cout << "Pausing..." << std::endl;
}

void HomePage::on_resume_button_clicked()
{
    std::cout << "Resuming..." << std::endl;
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
