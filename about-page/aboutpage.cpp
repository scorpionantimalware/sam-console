/**********************************************************************************/
/*                                                                                */
/* aboutpage.cpp                                                                  */
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


#include "aboutpage.hpp"

#include <iostream>
#include <QTimer>

AboutPage::AboutPage(QWidget *parent) : QWidget(parent), main_layout(nullptr) {
    // Initialize the main layout
    AboutPage::main_layout = new QVBoxLayout(this);
    AboutPage::main_layout->setSpacing(20);
}

AboutPage::~AboutPage()
{
    if (AboutPage::main_layout)
    {
        delete AboutPage::main_layout;
        AboutPage::main_layout = nullptr;
    }
}
