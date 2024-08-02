/**********************************************************************************/
/*                                                                                */
/* scanareascolumn.cpp                                                            */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware Console is a free Open Source Qt-powered frontend     */
/*    framework for SAM Engine.                                                   */
/*                                                                                */
/*    Copyright (c) 2024-present  (see AUTHORS.md).                               */
/*                                                                                */
/*    This program is free software: you can redistribute it and/or modify        */
/*    it under the terms of the GNU General Public License as published by        */
/*    the Free Software Foundation, either version 3 of the License, or           */
/*    (at your option) any later version.                                         */
/*                                                                                */
/*    This program is distributed in the hope that it will be useful,             */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of              */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               */
/*    GNU General Public License for more details.                                */
/*                                                                                */
/*    You should have received a copy of the GNU General Public License           */
/*    along with this program.  If not, see <https://www.gnu.org/licenses/>.      */
/*                                                                                */
/**********************************************************************************/

#include "scan-areas-controller/scanareascontroller.hpp"

ScanAreasController::ScanAreasController(QWidget *parent) :
		QWidget(parent), main_layout(nullptr), scan_areas_column(nullptr), buttons_layout(nullptr), add_new_button(nullptr), edit_button(nullptr), browse_button(nullptr), delete_button(nullptr) {
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

ScanAreasController::~ScanAreasController() {
	if (ScanAreasController::scan_areas_column) {
		delete ScanAreasController::scan_areas_column;
		ScanAreasController::scan_areas_column = nullptr;
	}

	if (ScanAreasController::add_new_button) {
		delete ScanAreasController::add_new_button;
		ScanAreasController::add_new_button = nullptr;
	}

	if (ScanAreasController::edit_button) {
		delete ScanAreasController::edit_button;
		ScanAreasController::edit_button = nullptr;
	}

	if (ScanAreasController::browse_button) {
		delete ScanAreasController::browse_button;
		ScanAreasController::browse_button = nullptr;
	}

	if (ScanAreasController::delete_button) {
		delete ScanAreasController::delete_button;
		ScanAreasController::delete_button = nullptr;
	}

	if (ScanAreasController::buttons_layout) {
		delete ScanAreasController::buttons_layout;
		ScanAreasController::buttons_layout = nullptr;
	}

	if (ScanAreasController::main_layout) {
		delete ScanAreasController::main_layout;
		ScanAreasController::main_layout = nullptr;
	}
}

void ScanAreasController::add_new_area() const {
}

void ScanAreasController::edit_existing_area() const {
}

void ScanAreasController::browse_filesystem_for_area() const {
	emit area_browse_button_clicked();
}

void ScanAreasController::delete_existing_area() const {
}
