/**********************************************************************************/
/*                                                                                */
/* fimpage.cpp                                                                    */
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


#include "fimpage.hpp"

#include <iostream>
#include <QTimer>

FIMPage::FIMPage(QWidget *parent) : QWidget(parent), main_layout(nullptr), events_monitor(nullptr) {
    // Initialize the main layout
    FIMPage::main_layout = new QVBoxLayout(this);
    FIMPage::main_layout->setSpacing(20);

    FIMPage::events_monitor = new EventsMonitor();

    FIMPage::main_layout->addWidget(FIMPage::events_monitor, 1);
}

FIMPage::~FIMPage()
{
    if (FIMPage::events_monitor)
    {
        delete FIMPage::events_monitor;
        FIMPage::events_monitor = nullptr;
    }

    if (FIMPage::main_layout)
    {
        delete FIMPage::main_layout;
        FIMPage::main_layout = nullptr;
    }
}

EventsMonitor *FIMPage::get_events_monitor_p() const
{
    return FIMPage::events_monitor;
}

