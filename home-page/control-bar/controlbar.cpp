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

#include "control-bar/controlbar.hpp"

ControlBar::ControlBar(QWidget *parent) : QWidget(parent), main_layout(nullptr), scan_button(nullptr), stop_button(nullptr), pause_button(nullptr), resume_button(nullptr), scan_areas_controller_button(nullptr) {

    ControlBar::main_layout = new QHBoxLayout(this);
    ControlBar::main_layout->setSpacing(20);
    ControlBar::main_layout->setAlignment(Qt::AlignCenter);

    ControlBar::scan_button = new ScanButton();
    ControlBar::stop_button = new StopButton();
    ControlBar::pause_button = new PauseButton();
    ControlBar::resume_button = new ResumeButton();
    ControlBar::scan_areas_controller_button = new ScanAreasControllerButton();

    ControlBar::main_layout->addWidget(ControlBar::scan_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::stop_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::pause_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::resume_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::scan_areas_controller_button, 1);

    this->setLayout(ControlBar::main_layout);
    this->setContentsMargins(10, 10, 10, 10); // left, top, right, and bottom respectively.

    this->connect(ControlBar::scan_button, &QPushButton::released, this, &ControlBar::start_scan);
    this->connect(ControlBar::stop_button, &QPushButton::released, this, &ControlBar::stop_scan);
    this->connect(ControlBar::pause_button, &QPushButton::released, this, &ControlBar::pause_scan);
    this->connect(ControlBar::resume_button, &QPushButton::released, this, &ControlBar::resume_scan);
    this->connect(ControlBar::scan_areas_controller_button, &QPushButton::released, this, &ControlBar::open_scan_areas_controller);

    // This is temporary until the stop, pause, and resume features are implemented.
    ControlBar::scan_button->setEnabled(true);
    ControlBar::stop_button->setEnabled(false);
    ControlBar::pause_button->setEnabled(false);
    ControlBar::resume_button->setEnabled(false);
    ControlBar::scan_areas_controller_button->setEnabled(true);
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

    if (ControlBar::resume_button) {
        delete ControlBar::resume_button;
        ControlBar::resume_button = nullptr;
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
    emit stop_button_clicked();
}

void ControlBar::pause_scan() {
    emit pause_button_clicked();
}

void ControlBar::resume_scan() {
    emit resume_button_clicked();
}

void ControlBar::open_scan_areas_controller() {
    emit scan_areas_controller_button_clicked();
}
