/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanareascontrollerbutton.cpp - Part of Scorpion Anti-malware
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

#include "control-bar/scanareascontrollerbutton.hpp"

#include <QWidget>
#include <cmath>

ScanAreasControllerButton::ScanAreasControllerButton()
{
    this->setFixedSize(150, 100);
}

void ScanAreasControllerButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w {this->width()};
    int h {this->height()};

    float min_side {(float)qMin(w, h)};

    QPointF center {w * 0.5f, h * 0.5f};

    QPen pen(Qt::SolidLine); // Set pen style to SolidLine
    pen.setColor(Qt::black); // Set pen color
    pen.setWidth(min_side * 0.08f); // Set pen width to control stroke thickness
    painter.setPen(pen);

    // Draw the lens.
    QPointF lens_circle_center {center - QPointF(min_side * 0.1f, min_side * 0.1f)};
    float lens_circle_radius {min_side * 0.22f};
    painter.drawEllipse(lens_circle_center, lens_circle_radius, lens_circle_radius);

    // Draw the line.

    /*
        Here we start from the circle boundary (we get the circle boundary by adding the radius
        on the lens' center toward -45 direction).
    */
    float direction {qDegreesToRadians(45.0f)};
    QPointF line_start {lens_circle_center + QPointF(lens_circle_radius * cos(direction), lens_circle_radius * sin(direction))};

    /*
        Here we add the radius to the line start point (toward -45 direction) to get the 
        line end point.
    */
    QPointF line_end {line_start + QPointF(lens_circle_radius * cos(direction), lens_circle_radius * sin(direction))};
    painter.drawLine(line_start, line_end);
}
