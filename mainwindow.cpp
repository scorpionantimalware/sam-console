/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * mainwindow.cpp
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

#include "mainwindow.hpp"

#include <iostream>
#include <QTimer>

#define SPLASH_SCREEN_DELAY 2000

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), splash_screen(nullptr), main_layout(nullptr), page_switcher_bar(nullptr), pages_stack(nullptr), home_page(nullptr), fim_page(nullptr) {
    // TODO: This splash screen works fine but it crashes when pressing the 
    // scan button. I will need to investigate this further.

    // MainWindow::splash_screen = new SAMConsoleSplash();

    // Add splash screen to the main layout
    // MainWindow::main_layout->addWidget(MainWindow::splash_screen);

    // Use QTimer to remove splash screen and show main items after a delay
    // QTimer::singleShot(SPLASH_SCREEN_DELAY, this, &MainWindow::show_main_ui);

    MainWindow::show_main_ui();
}

MainWindow::~MainWindow()
{
    if (MainWindow::home_page)
    {
        delete MainWindow::home_page;
        MainWindow::home_page = nullptr;
    }

    if (MainWindow::fim_page)
    {
        delete MainWindow::fim_page;
        MainWindow::fim_page = nullptr;
    }

    if (MainWindow::pages_stack)
    {
        delete MainWindow::pages_stack;
        MainWindow::pages_stack = nullptr;
    }

    if (MainWindow::page_switcher_bar)
    {
        delete MainWindow::page_switcher_bar;
        MainWindow::page_switcher_bar = nullptr;
    }

    if (MainWindow::main_layout)
    {
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

HomePage* MainWindow::get_home_page_p() const
{
    return MainWindow::home_page;
}

FIMPage* MainWindow::get_fim_page_p() const
{
    return MainWindow::fim_page;
}

void MainWindow::on_home_page_switch_button_clicked()
{
    std::cout << "Showing home page" << std::endl;
    MainWindow::pages_stack->setCurrentIndex(0); // Show the home page
}

void MainWindow::on_fim_page_switch_button_clicked()
{
    std::cout << "Showing FIM page" << std::endl;
    MainWindow::pages_stack->setCurrentIndex(1); // Show the FIM page
}
