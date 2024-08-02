/**********************************************************************************/
/*                                                                                */
/* mainwindow.cpp                                                                 */
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

#include "mainwindow.hpp"

#include <QTimer>
#include <iostream>

#define SPLASH_SCREEN_DELAY 2000

MainWindow::MainWindow(QWidget *parent) :
		QWidget(parent), splash_screen(nullptr), main_layout(nullptr), page_switcher_bar(nullptr), pages_stack(nullptr), home_page(nullptr), fim_page(nullptr) {
	// TODO: This splash screen works fine but it crashes when pressing the
	// scan button. I will need to investigate this further.

	// MainWindow::splash_screen = new SAMConsoleSplash();

	// Add splash screen to the main layout
	// MainWindow::main_layout->addWidget(MainWindow::splash_screen);

	// Use QTimer to remove splash screen and show main items after a delay
	// QTimer::singleShot(SPLASH_SCREEN_DELAY, this, &MainWindow::show_main_ui);

	MainWindow::show_main_ui();
}

MainWindow::~MainWindow() {
	if (MainWindow::home_page) {
		delete MainWindow::home_page;
		MainWindow::home_page = nullptr;
	}

	if (MainWindow::fim_page) {
		delete MainWindow::fim_page;
		MainWindow::fim_page = nullptr;
	}

	if (MainWindow::pages_stack) {
		delete MainWindow::pages_stack;
		MainWindow::pages_stack = nullptr;
	}

	if (MainWindow::page_switcher_bar) {
		delete MainWindow::page_switcher_bar;
		MainWindow::page_switcher_bar = nullptr;
	}

	if (MainWindow::main_layout) {
		delete MainWindow::main_layout;
		MainWindow::main_layout = nullptr;
	}
}

void MainWindow::show_main_ui() {
	// Remove splash screen
	// MainWindow::main_layout->removeWidget(MainWindow::splash_screen);

	// Delete the splash screen
	// if (MainWindow::splash_screen)
	// {
	//     delete MainWindow::splash_screen;
	//     MainWindow::splash_screen = nullptr;
	// }

	// Initialize the page switcher bar
	MainWindow::page_switcher_bar = new PageSwitcherBar();

	// Initialize the pages stack
	MainWindow::pages_stack = new QStackedWidget();

	// Initialize the home page
	MainWindow::home_page = new HomePage();

	// Initialize the FIM page
	MainWindow::fim_page = new FIMPage();

	// Add pages to the stack
	MainWindow::pages_stack->addWidget(MainWindow::home_page); // Index 0
	MainWindow::pages_stack->addWidget(MainWindow::fim_page); // Index 1

	// Initialize the main layout
	MainWindow::main_layout = new QHBoxLayout(this);
	MainWindow::main_layout->setSpacing(20);

	// Add main items to the layout
	MainWindow::main_layout->addWidget(MainWindow::page_switcher_bar, 1); // Take up 1/10 of the space
	MainWindow::main_layout->addWidget(MainWindow::pages_stack, 9); // Take up 9/10 of the space

	// Set initial page
	MainWindow::pages_stack->setCurrentIndex(0);

	// Connect signals and slots
	this->connect(MainWindow::page_switcher_bar, &PageSwitcherBar::home_page_switch_button_clicked, this, &MainWindow::on_home_page_switch_button_clicked);
	this->connect(MainWindow::page_switcher_bar, &PageSwitcherBar::fim_page_switch_button_clicked, this, &MainWindow::on_fim_page_switch_button_clicked);
}

HomePage *MainWindow::get_home_page_p() const {
	return MainWindow::home_page;
}

FIMPage *MainWindow::get_fim_page_p() const {
	return MainWindow::fim_page;
}

void MainWindow::on_home_page_switch_button_clicked() const {
	// If we are in the home page, do nothing
	if (MainWindow::pages_stack->currentIndex() == 0) {
		return;
	}

	std::cout << "Showing home page" << std::endl;
	MainWindow::pages_stack->setCurrentIndex(0); // Show the home page
}

void MainWindow::on_fim_page_switch_button_clicked() const {
	// If we are in the FIM page, do nothing
	if (MainWindow::pages_stack->currentIndex() == 1) {
		return;
	}

	std::cout << "Showing FIM page" << std::endl;
	MainWindow::pages_stack->setCurrentIndex(1); // Show the FIM page
}
