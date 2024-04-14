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

#include "scanareascontroller.hpp"

ScanAreasController::ScanAreasController(QWidget *parent) : QWidget(parent), main_layout(nullptr), scan_areas_column(nullptr)
{
    ScanAreasController::main_layout = new QHBoxLayout(this);

    ScanAreasController::scan_areas_column = new ScanAreasColumn();

    ScanAreasController::main_layout->addWidget(ScanAreasController::scan_areas_column);

    ScanAreasController::controller = new QVBoxLayout();
    ScanAreasController::controller->setSpacing(10);
    ScanAreasController::controller->setAlignment(Qt::AlignTop);

    ScanAreasController::new_area_button = new QPushButton("New");
    ScanAreasController::edit_area_button = new QPushButton("Edit");
    ScanAreasController::browse_area_button = new QPushButton("Browse");
    ScanAreasController::delete_area_button = new QPushButton("Delete");

    ScanAreasController::controller->addWidget(ScanAreasController::new_area_button);
    ScanAreasController::controller->addWidget(ScanAreasController::edit_area_button);
    ScanAreasController::controller->addWidget(ScanAreasController::browse_area_button);
    ScanAreasController::controller->addWidget(ScanAreasController::delete_area_button);

    ScanAreasController::main_layout->addLayout(ScanAreasController::controller);

    this->connect(ScanAreasController::browse_area_button, &QPushButton::released, this, &ScanAreasController::browse_area);
    this->connect(this, &ScanAreasController::browse_area_button_clicked, scan_areas_column, &ScanAreasColumn::on_browse_area_button_clicked);
}

ScanAreasController::~ScanAreasController()
{
    if (ScanAreasController::scan_areas_column)
    {
        delete ScanAreasController::scan_areas_column;
        ScanAreasController::scan_areas_column = nullptr;
    }

    if (ScanAreasController::new_area_button)
    {
        delete ScanAreasController::new_area_button;
        ScanAreasController::new_area_button = nullptr;
    }

    if (ScanAreasController::edit_area_button)
    {
        delete ScanAreasController::edit_area_button;
        ScanAreasController::edit_area_button = nullptr;
    }

    if (ScanAreasController::browse_area_button)
    {
        delete ScanAreasController::browse_area_button;
        ScanAreasController::browse_area_button = nullptr;
    }

    if (ScanAreasController::delete_area_button)
    {
        delete ScanAreasController::delete_area_button;
        ScanAreasController::delete_area_button = nullptr;
    }

    if (ScanAreasController::controller)
    {
        delete ScanAreasController::controller;
        ScanAreasController::controller = nullptr;
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

void ScanAreasController::edit_area()
{
}

void ScanAreasController::browse_area()
{
    emit browse_area_button_clicked();
}

void ScanAreasController::delete_area()
{
}
