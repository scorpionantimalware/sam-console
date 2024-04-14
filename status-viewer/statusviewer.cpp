/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * statusviewer.cpp - A class that displays the status of the scan.
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

    // this->setEnabled(false);
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

    if (StatusViewer::main_layout)
    {
        delete StatusViewer::main_layout;
        StatusViewer::main_layout = nullptr;
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

    /*
        -1.0 is the default value for the buffer that is being sent to the model.
        If the model is not able to predict the file, it will not fill the buffer.
    */
    std::string status {prediction == -1.0f ? "Failed" : prediction > 0.5f ? "Malware" : "Benign"};
    StatusViewer::summary->set_status_for_row(row_index, status, prediction);
}

void StatusViewer::on_scan_button_clicked()
{
    // this->setEnabled(true);

    if (!engine)
    { 
        std::cout << "Error: Engine not found" << std::endl;
        return;
    }

    std::cout << "Scanning..." << std::endl;
    engine->scan();
}
