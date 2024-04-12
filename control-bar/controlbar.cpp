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
