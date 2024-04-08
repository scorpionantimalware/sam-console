#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), main_layout(nullptr), control_bar(nullptr), status_viewer(nullptr){
    main_layout = new QVBoxLayout(this);

    main_layout->setSpacing(20);

    control_bar = new ControlBar();
    status_viewer = new StatusViewer();


    // Add left bar to the main layout
    main_layout->addWidget(control_bar, 1);
    main_layout->addWidget(status_viewer, 3); // The viewer will take up 3/4 of the space.

    connect(control_bar, &ControlBar::scan_started, status_viewer, &StatusViewer::on_scan_clicked);
}

MainWindow::~MainWindow()
{
    if (status_viewer)
    {
        delete status_viewer;
        status_viewer = nullptr;
    }

    if (control_bar)
    {
        delete control_bar;
        control_bar = nullptr;
    }

    if (main_layout)
    {
        delete main_layout;
        main_layout = nullptr;
    }
}



