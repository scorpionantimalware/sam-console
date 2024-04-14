/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanbutton.cpp - A class that represents the scan button in the control bar.
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

#include "scanbutton.hpp"

#include <QWidget>

ScanButton::ScanButton()
{
    this->setFixedSize(100, 100);
}

ScanButton::~ScanButton()
{
}

void ScanButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float min_side {(float)qMin(width(), height())};
    
    QPointF center {width() * 0.5f, height() * 0.5f};

    float vc_length {min_side * 0.25f}; // Length from each triangle's vertex to the center of the widget

    // Calculate the vertices of the triangle based on the center of the widget
    QPointF top_v {center + QPointF(vc_length, 0)};
    QPointF bottom_left_v {center - QPointF(vc_length, vc_length)};
    QPointF bottom_right_v {center - QPointF(vc_length, -vc_length)};

    // Draw the triangle
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    painter.drawPolygon(QPolygonF() << top_v << bottom_left_v << bottom_right_v);
}
