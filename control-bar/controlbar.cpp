/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * controlbar.cpp - A class that represents the control bar of the application.
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

#include "controlbar.hpp"

ControlBar::ControlBar() : main_layout(nullptr), scan_button(nullptr), stop_button(nullptr), pause_button(nullptr), scan_areas_controller_button(nullptr){

    ControlBar::main_layout = new QHBoxLayout(this);
    ControlBar::main_layout->setSpacing(20);
    ControlBar::main_layout->setAlignment(Qt::AlignCenter);

    ControlBar::scan_button = new ScanButton();
    ControlBar::stop_button = new StopButton();
    ControlBar::pause_button = new PauseButton();
    ControlBar::scan_areas_controller_button = new ScanAreasControllerButton();

    ControlBar::main_layout->addWidget(ControlBar::scan_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::stop_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::pause_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::scan_areas_controller_button, 1);

    this->setLayout(ControlBar::main_layout);
    this->setContentsMargins(10, 10, 10, 10); // left, top, right, and bottom respectively.

    this->connect(ControlBar::scan_button, &QPushButton::released, this, &ControlBar::start_scan);
    this->connect(ControlBar::scan_areas_controller_button, &QPushButton::released, this, &ControlBar::show_scan_areas_controller);
}

ControlBar::~ControlBar() {
    if (ControlBar::scan_button) {
        delete ControlBar::scan_button;
        ControlBar::scan_button = nullptr;
    }

    if (ControlBar::stop_button) {
        delete ControlBar::stop_button;
        ControlBar::stop_button = nullptr;
    }

    if (ControlBar::pause_button) {
        delete ControlBar::pause_button;
        ControlBar::pause_button = nullptr;
    }

    if (ControlBar::scan_areas_controller_button) {
        delete ControlBar::scan_areas_controller_button;
        ControlBar::scan_areas_controller_button = nullptr;
    }

    if (ControlBar::main_layout) {
        delete ControlBar::main_layout;
        ControlBar::main_layout = nullptr;
    }
}

void ControlBar::start_scan() {
    emit scan_button_clicked();
}

void ControlBar::stop_scan() {
}

void ControlBar::pause_scan() {
}

void ControlBar::show_scan_areas_controller() {
    emit scan_areas_controller_button_clicked();
}
