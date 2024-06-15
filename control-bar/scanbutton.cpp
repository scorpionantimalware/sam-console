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

ScanButton::ScanButton() : state(ScanButton::TextureState::IDLE), current_loading_arc_angle(0), loading_arc_animator(nullptr)
{
    this->setFixedSize(100, 100);
    ScanButton::loading_arc_animator = new QPropertyAnimation(this, "loading_arc_angle");
    ScanButton::loading_arc_animator->setDuration(2000); // Duration of one full rotation
    ScanButton::loading_arc_animator->setStartValue(0);
    ScanButton::loading_arc_animator->setEndValue(360 * 16);
    ScanButton::loading_arc_animator->setLoopCount(-1); // Loop indefinitely
}

ScanButton::~ScanButton()
{
    if (ScanButton::loading_arc_animator)
    {
        delete ScanButton::loading_arc_animator;
        ScanButton::loading_arc_animator = nullptr;
    }
}

void ScanButton::set_state(const ScanButton::TextureState& new_state) {
    ScanButton::state = new_state;
    switch (ScanButton::state)
    {
        case ScanButton::TextureState::IDLE:
            ScanButton::loading_arc_animator->stop();
            ScanButton::set_loading_arc_angle(0); // Reset angle when not scanning
            break;
        case ScanButton::TextureState::SCANNING:
            ScanButton::loading_arc_animator->start();
            break;
        case ScanButton::TextureState::ERROR:
            ScanButton::loading_arc_animator->stop();
            break;
        default:
            break;
    }
    this->update(); // Trigger a repaint
}

int ScanButton::loading_arc_angle() const {
    return ScanButton::current_loading_arc_angle;
}

void ScanButton::set_loading_arc_angle(const int& angle) {
    if (ScanButton::current_loading_arc_angle == angle) {
        return;
    }

    ScanButton::current_loading_arc_angle = angle;
    emit ScanButton::loading_arc_angle_changed();
    this->update(); // Trigger a repaint
}

void ScanButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float min_side {(float)qMin(width(), height())};
    
    QPointF center {width() * 0.5f, height() * 0.5f};

    switch (ScanButton::state)
    {
        case ScanButton::TextureState::IDLE: {
            float vc_length {min_side * 0.25f}; // Length from each triangle's vertex to the center of the widget

            // Calculate the vertices of the triangle based on the center of the widget
            QPointF top_v {center + QPointF(vc_length, 0)};
            QPointF bottom_left_v {center - QPointF(vc_length, vc_length)};
            QPointF bottom_right_v {center - QPointF(vc_length, -vc_length)};

            // Draw the triangle
            painter.setBrush(Qt::green);
            painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
            painter.drawPolygon(QPolygonF() << top_v << bottom_left_v << bottom_right_v);
            break;
        }
        case ScanButton::TextureState::SCANNING: {
            QPen pen(Qt::SolidLine); // Set pen style to SolidLine
            pen.setColor(Qt::black); // Set pen color
            pen.setWidth(min_side * 0.08f); // Set pen width to control stroke thickness
            painter.setPen(pen);

            // Example of a rotating arc for the scanning state
            QRectF rect(center.x() - min_side * 0.25, center.y() - min_side * 0.25, min_side * 0.5, min_side * 0.5);
            const int span_angle {90 * 16}; // Span angle (in 1/16th of a degree)

            painter.drawArc(rect, ScanButton::current_loading_arc_angle, span_angle);
            break;
        }
        case ScanButton::TextureState::ERROR: {
            // Draw the error icon (e.g., a red cross or a warning symbol)
            painter.setBrush(Qt::red);
            painter.setPen(Qt::NoPen);

            // Example of a red cross for the error state
            float crossSize = min_side * 0.2f;
            QLineF line1(center - QPointF(crossSize, crossSize), center + QPointF(crossSize, crossSize));
            QLineF line2(center - QPointF(crossSize, -crossSize), center + QPointF(crossSize, -crossSize));

            QPen pen(Qt::red, 4);
            painter.setPen(pen);
            painter.drawLine(line1);
            painter.drawLine(line2);
            break;
        }
        default:
            break;
    }
}
