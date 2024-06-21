/**********************************************************************************/
/*                                                                                */
/* samconsolesplash.cpp                                                           */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware is a free Open Source AI-powered Anti-malware         */
/*    framework for Researchers.                                                  */
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


#include "samconsolesplash.hpp"

#define SAM_LOGO_ORIGINAL_WIDTH 1014.873f
#define SAM_LOGO_ORIGINAL_HEIGHT 412.133f

SAMConsoleSplash::SAMConsoleSplash(QWidget *parent) : QWidget(parent), splash_layout(nullptr), svg_widget(nullptr)
{
    SAMConsoleSplash::splash_layout = new QVBoxLayout(this);

    SAMConsoleSplash::svg_widget = new QSvgWidget(QString(SAM_CONSOLE_ROOTDIR) + '/' + QString("logo.svg"), this);

    // Calculate the desired size while maintaining aspect ratio
    const float desired_width {350.0f}; // Desired width
    float desired_height {desired_width * SAM_LOGO_ORIGINAL_HEIGHT / SAM_LOGO_ORIGINAL_WIDTH}; // Calculate height to maintain aspect ratio
    SAMConsoleSplash::svg_widget->setFixedSize((int)desired_width, (int)desired_height);
    SAMConsoleSplash::splash_layout->addWidget(SAMConsoleSplash::svg_widget);
    SAMConsoleSplash::splash_layout->setAlignment(Qt::AlignCenter);
}

SAMConsoleSplash::~SAMConsoleSplash()
{
    if (SAMConsoleSplash::svg_widget)
    {
        delete SAMConsoleSplash::svg_widget;
        SAMConsoleSplash::svg_widget = nullptr;
    }

    if (SAMConsoleSplash::splash_layout)
    {
        delete SAMConsoleSplash::splash_layout;
        SAMConsoleSplash::splash_layout = nullptr;
    }
}
