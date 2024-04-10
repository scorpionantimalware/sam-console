#include "statusviewer.hpp"

#include <iostream>

#include "samconsolemain.hpp"

StatusViewer::StatusViewer() : main_layout(nullptr), progress_bar(nullptr), summary(nullptr)
{
    StatusViewer::main_layout = new QVBoxLayout(this);
    StatusViewer::main_layout->setSpacing(10);
    
    StatusViewer::progress_bar = new QProgressBar();
    StatusViewer::progress_bar->setRange(0, 0); // Indeterminate progress
    StatusViewer::progress_bar->setAlignment(Qt::AlignCenter); // Center align the progress bar
    
    StatusViewer::summary = new Summary();

    StatusViewer::main_layout->addWidget(StatusViewer::progress_bar, 1);
    StatusViewer::main_layout->addWidget(StatusViewer::summary, 1);

    this->setEnabled(false);
}

StatusViewer::~StatusViewer()
{
    if (StatusViewer::progress_bar)
    {
        delete StatusViewer::progress_bar;
        StatusViewer::progress_bar = nullptr;
    }

    if (StatusViewer::summary)
    {
        delete StatusViewer::summary;
        StatusViewer::summary = nullptr;
    }
}

void StatusViewer::on_scan_fire()
{
    std::cout << "Scan fired" << std::endl;
}

void StatusViewer::on_scan_complete()
{
    std::cout << "Scan complete" << std::endl;
}

int StatusViewer::on_new_file(const std::string& filename)
{
    std::cout << "New file: " << filename << std::endl;
    return StatusViewer::summary->add_row(filename);
}

void StatusViewer::on_status(const int& row_index, const float& prediction)
{
    std::cout << "Status for row " << row_index << ": " << prediction << std::endl;
    std::string status {prediction == -1.0f ? "Failed" : prediction > 0.5f ? "Malware" : "Benign"};
    StatusViewer::summary->set_status_for_row(row_index, status, prediction);
}

void StatusViewer::on_scan_clicked()
{
    this->setEnabled(true);

    if (!engine)
    { 
        std::cout << "Error: Engine not found" << std::endl;
        return;
    }

    std::cout << "Scanning..." << std::endl;
    engine->scan();
}
