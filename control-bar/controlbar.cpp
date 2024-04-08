#include "controlbar.hpp"

#include "scanbutton.hpp"
#include "stopbutton.hpp"
#include "pausebutton.hpp"

ControlBar::ControlBar() {

    main_layout = new QHBoxLayout(this);
    main_layout->setSpacing(10);

    ScanButton *scan_button = new ScanButton();
    StopButton *stop_button = new StopButton();
    PauseButton *pause_button = new PauseButton();

    main_layout->addWidget(scan_button, 1);
    main_layout->addWidget(stop_button, 1);
    main_layout->addWidget(pause_button, 1);

    setLayout(main_layout);
    setContentsMargins(10, 10, 10, 10); // left, top, right, and bottom respectively.

    connect(scan_button, &QPushButton::released, this, &ControlBar::scan_button_clicked);
}

ControlBar::~ControlBar() {

}

void ControlBar::scan_button_clicked() {
    emit scan_started();
}
