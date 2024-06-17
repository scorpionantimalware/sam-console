/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanareascontroller.cpp
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

#include "scan-areas-controller/scanareascontroller.hpp"

ScanAreasController::ScanAreasController(QWidget *parent) : QWidget(parent), main_layout(nullptr), scan_areas_column(nullptr), buttons_layout(nullptr), add_new_button(nullptr), edit_button(nullptr), browse_button(nullptr), delete_button(nullptr) {
    this->setWindowTitle("Scan Areas Controller");

    ScanAreasController::main_layout = new QHBoxLayout(this);

    ScanAreasController::scan_areas_column = new ScanAreasColumn();

    ScanAreasController::main_layout->addWidget(ScanAreasController::scan_areas_column);

    ScanAreasController::buttons_layout = new QVBoxLayout();
    ScanAreasController::buttons_layout->setSpacing(10);
    ScanAreasController::buttons_layout->setAlignment(Qt::AlignTop);

    ScanAreasController::add_new_button = new QPushButton("New");
    ScanAreasController::edit_button = new QPushButton("Edit");
    ScanAreasController::browse_button = new QPushButton("Browse");
    ScanAreasController::delete_button = new QPushButton("Delete");

    ScanAreasController::buttons_layout->addWidget(ScanAreasController::add_new_button);
    ScanAreasController::buttons_layout->addWidget(ScanAreasController::edit_button);
    ScanAreasController::buttons_layout->addWidget(ScanAreasController::browse_button);
    ScanAreasController::buttons_layout->addWidget(ScanAreasController::delete_button);

    ScanAreasController::main_layout->addLayout(ScanAreasController::buttons_layout);

    this->connect(ScanAreasController::browse_button, &QPushButton::released, this, &ScanAreasController::browse_filesystem_for_area);
    this->connect(this, &ScanAreasController::area_browse_button_clicked, scan_areas_column, &ScanAreasColumn::on_area_browse_button_clicked);
}

ScanAreasController::~ScanAreasController()
{
    if (ScanAreasController::scan_areas_column)
    {
        delete ScanAreasController::scan_areas_column;
        ScanAreasController::scan_areas_column = nullptr;
    }

    if (ScanAreasController::add_new_button)
    {
        delete ScanAreasController::add_new_button;
        ScanAreasController::add_new_button = nullptr;
    }

    if (ScanAreasController::edit_button)
    {
        delete ScanAreasController::edit_button;
        ScanAreasController::edit_button = nullptr;
    }

    if (ScanAreasController::browse_button)
    {
        delete ScanAreasController::browse_button;
        ScanAreasController::browse_button = nullptr;
    }

    if (ScanAreasController::delete_button)
    {
        delete ScanAreasController::delete_button;
        ScanAreasController::delete_button = nullptr;
    }

    if (ScanAreasController::buttons_layout)
    {
        delete ScanAreasController::buttons_layout;
        ScanAreasController::buttons_layout = nullptr;
    }

    if (ScanAreasController::main_layout)
    {
        delete ScanAreasController::main_layout;
        ScanAreasController::main_layout = nullptr;
    }
}

void ScanAreasController::add_new_area()
{
}

void ScanAreasController::edit_existing_area()
{
}

void ScanAreasController::browse_filesystem_for_area()
{
    emit area_browse_button_clicked();
}

void ScanAreasController::delete_existing_area()
{
}
