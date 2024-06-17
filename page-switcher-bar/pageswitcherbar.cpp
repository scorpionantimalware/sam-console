/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pageswitcherbar.cpp
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

#include "pageswitcherbar.hpp"


PageSwitcherBar::PageSwitcherBar(QWidget *parent) : QWidget(parent), main_layout(nullptr), home_page_button(nullptr), fim_page_button(nullptr) {
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

PageSwitcherBar::~PageSwitcherBar()
{
    if (PageSwitcherBar::home_page_button)
    {
        delete PageSwitcherBar::home_page_button;
        PageSwitcherBar::home_page_button = nullptr;
    }

    if (PageSwitcherBar::fim_page_button)
    {
        delete PageSwitcherBar::fim_page_button;
        PageSwitcherBar::fim_page_button = nullptr;
    }

    if (PageSwitcherBar::main_layout)
    {
        delete PageSwitcherBar::main_layout;
        PageSwitcherBar::main_layout = nullptr;
    }
}

void PageSwitcherBar::switch_to_home_page()
{
    emit home_page_switch_button_clicked();
}

void PageSwitcherBar::switch_to_fim_page()
{
    emit fim_page_switch_button_clicked();
}
