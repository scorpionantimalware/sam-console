/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * samconsolesplash.cpp
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
