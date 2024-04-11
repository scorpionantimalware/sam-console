#include "controlbar.hpp"

ControlBar::ControlBar() : main_layout(nullptr), scan_button(nullptr), stop_button(nullptr), pause_button(nullptr), scan_areas_processor_button(nullptr){

    ControlBar::main_layout = new QHBoxLayout(this);
    ControlBar::main_layout->setSpacing(20);
    ControlBar::main_layout->setAlignment(Qt::AlignCenter);

    ControlBar::scan_button = new ScanButton();
    ControlBar::stop_button = new StopButton();
    ControlBar::pause_button = new PauseButton();
    ControlBar::scan_areas_processor_button = new ScanAreasControllerButton();

    ControlBar::main_layout->addWidget(ControlBar::scan_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::stop_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::pause_button, 1);
    ControlBar::main_layout->addWidget(ControlBar::scan_areas_processor_button, 1);

    this->setLayout(ControlBar::main_layout);
    this->setContentsMargins(10, 10, 10, 10); // left, top, right, and bottom respectively.

    this->connect(ControlBar::scan_button, &QPushButton::released, this, &ControlBar::scan_button_clicked);
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

    if (ControlBar::scan_areas_processor_button) {
        delete ControlBar::scan_areas_processor_button;
        ControlBar::scan_areas_processor_button = nullptr;
    }

    if (ControlBar::main_layout) {
        delete ControlBar::main_layout;
        ControlBar::main_layout = nullptr;
    }
}

void ControlBar::scan_button_clicked() {
    emit scan_started();
}

void ControlBar::stop_button_clicked() {
    // emit scan_stopped();
}

void ControlBar::pause_button_clicked() {
    // emit scan_paused();
}

void ControlBar::scan_areas_processor_button_clicked() {
    // emit scan_areas_processor();
}
