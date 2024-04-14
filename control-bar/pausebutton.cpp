/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pausebutton.cpp - A class that represents the pause button in the control bar.
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

#include "pausebutton.hpp"

#include <QWidget>

PauseButton::PauseButton()
{
    this->setFixedSize(100, 100);
}

PauseButton::~PauseButton()
{
    
}

void PauseButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float min_side {(float)qMin(width(), height())};

    // Use Multiplication instead of Division as it is faster
    QPointF center {width() * 0.5f, height() * 0.5f};

    float max_height {min_side * 0.18f}; // Max height of the pause symbol from the center.
    float separation {min_side * 0.15f};
    float pen_width {separation};

    QPen pen(Qt::black);
    pen.setWidth(pen_width);
    painter.setPen(pen);

    /*
        From top to bottom, draw the left part.
    */
    painter.drawLine(center - QPointF(separation, max_height), center - QPointF(separation, -max_height));

    /*
        From top to bottom, draw the right part.
    */
    painter.drawLine(center + QPointF(separation, -max_height), center + QPointF(separation, max_height));
}
