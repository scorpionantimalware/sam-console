#include "mainwindow.hpp"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), main_layout(nullptr), control_bar(nullptr), results_stream_viewer(nullptr), scan_areas_controller(nullptr) {
    MainWindow::main_layout = new QVBoxLayout(this);

    MainWindow::main_layout->setSpacing(20);

    MainWindow::control_bar = new ControlBar();
    MainWindow::results_stream_viewer = new ResultsStreamViewer();

    MainWindow::main_layout->addWidget(MainWindow::control_bar, 1);
    MainWindow::main_layout->addWidget(MainWindow::results_stream_viewer, 3); // The viewer will take up 3/4 of the space.

    this->connect(MainWindow::control_bar, &ControlBar::scan_button_clicked, MainWindow::results_stream_viewer, &ResultsStreamViewer::on_scan_button_clicked);
    this->connect(MainWindow::control_bar, &ControlBar::scan_areas_controller_button_clicked, this, &MainWindow::on_scan_areas_controller_button_clicked);
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
        MainWindow::scan_areas_controller->show();
    }
    
    MainWindow::scan_areas_controller->show();
}
