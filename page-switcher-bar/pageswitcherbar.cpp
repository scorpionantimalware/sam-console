/**********************************************************************************/
/*                                                                                */
/* pageswitcherbar.cpp                                                            */
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

#include "pageswitcherbar.hpp"

PageSwitcherBar::PageSwitcherBar(QWidget *parent) :
		QWidget(parent), main_layout(nullptr), home_page_button(nullptr), fim_page_button(nullptr) {
	// Initialize the main layout
	PageSwitcherBar::main_layout = new QVBoxLayout(this);

	// Initialize the home page button
	PageSwitcherBar::home_page_button = new QPushButton("Home");

	// Initialize the FIM page button
	PageSwitcherBar::fim_page_button = new QPushButton("FIM");

	PageSwitcherBar::main_layout->addWidget(PageSwitcherBar::home_page_button);
	PageSwitcherBar::main_layout->addWidget(PageSwitcherBar::fim_page_button);
	PageSwitcherBar::main_layout->addStretch();

	connect(PageSwitcherBar::home_page_button, &QPushButton::released, this, &PageSwitcherBar::switch_to_home_page);
	connect(PageSwitcherBar::fim_page_button, &QPushButton::released, this, &PageSwitcherBar::switch_to_fim_page);
}

PageSwitcherBar::~PageSwitcherBar() {
	if (PageSwitcherBar::home_page_button) {
		delete PageSwitcherBar::home_page_button;
		PageSwitcherBar::home_page_button = nullptr;
	}

	if (PageSwitcherBar::fim_page_button) {
		delete PageSwitcherBar::fim_page_button;
		PageSwitcherBar::fim_page_button = nullptr;
	}

	if (PageSwitcherBar::main_layout) {
		delete PageSwitcherBar::main_layout;
		PageSwitcherBar::main_layout = nullptr;
	}
}

void PageSwitcherBar::switch_to_home_page() const {
	emit home_page_switch_button_clicked();
}

void PageSwitcherBar::switch_to_fim_page() const {
	emit fim_page_switch_button_clicked();
}
