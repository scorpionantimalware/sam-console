#include "mainwindow.h"

#include "control-bar/controlbar.h"
#include "status-viewer/statusviewer.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    main_layout = new QVBoxLayout(this);

    main_layout->setSpacing(20);

    ControlBar *control_bar = new ControlBar();
    StatusViewer *status_viewer = new StatusViewer();


    // Add left bar to the main layout
    main_layout->addWidget(control_bar, 1);
    main_layout->addWidget(status_viewer, 3); // The viewer will take up 3/4 of the space.

    connect(control_bar, &ControlBar::scan_started, status_viewer, &StatusViewer::on_scan_clicked);
}

MainWindow::~MainWindow()
{
}



