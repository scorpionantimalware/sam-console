/**********************************************************************************/
/*                                                                                */
/* scanbutton.cpp                                                                 */
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

#include "control-bar/scanbutton.hpp"

#define LOADING_ARC_CYCLE_DURATION 1500 // Duration of one full rotation

ScanButton::ScanButton() :
		state(ScanButton::TextureState::IDLE), current_loading_arc_angle(0), loading_arc_animator(nullptr) {
	this->setFixedSize(100, 100);
	ScanButton::loading_arc_animator = new QPropertyAnimation(this, "loading_arc_angle");
	ScanButton::loading_arc_animator->setDuration(LOADING_ARC_CYCLE_DURATION); // Duration of one full rotation
	ScanButton::loading_arc_animator->setStartValue(0);
	ScanButton::loading_arc_animator->setEndValue(360 * 16);
	ScanButton::loading_arc_animator->setLoopCount(-1); // Loop indefinitely
}

ScanButton::~ScanButton() {
	if (ScanButton::loading_arc_animator) {
		delete ScanButton::loading_arc_animator;
		ScanButton::loading_arc_animator = nullptr;
	}
}

void ScanButton::set_state(const ScanButton::TextureState &new_state) {
	ScanButton::state = new_state;
	switch (ScanButton::state) {
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

void ScanButton::set_loading_arc_angle(const int &angle) {
	if (ScanButton::current_loading_arc_angle == angle) {
		return;
	}

	ScanButton::current_loading_arc_angle = angle;
	emit ScanButton::loading_arc_angle_changed();
	this->update(); // Trigger a repaint
}

void ScanButton::paintEvent(QPaintEvent *event) {
	QPushButton::paintEvent(event);

	QPainter painter = QPainter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int w{ this->width() };
	int h{ this->height() };

	float min_side{ (float)qMin(w, h) };

	QPointF center{ w * 0.5f, h * 0.5f };

	switch (ScanButton::state) {
		case ScanButton::TextureState::IDLE: {
			float vc_length{ min_side * 0.25f }; // Length from each triangle's vertex to the center of the widget

			// Calculate the vertices of the triangle based on the center of the widget
			QPointF top_v{ center + QPointF(vc_length, 0) };
			QPointF bottom_left_v{ center - QPointF(vc_length, vc_length) };
			QPointF bottom_right_v{ center - QPointF(vc_length, -vc_length) };

			// Draw the triangle
			painter.setBrush(Qt::green);
			painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
			painter.drawPolygon(QPolygonF() << top_v << bottom_left_v << bottom_right_v);
			break;
		}
		case ScanButton::TextureState::SCANNING: {
			QRectF rect(center.x() - min_side * 0.25, center.y() - min_side * 0.25, min_side * 0.5, min_side * 0.5);
			const int span_angle{ 60 * 16 }; // Span angle (in 1/16th of a degree)

			QPen pen(Qt::SolidLine); // Set pen style to SolidLine
			pen.setColor(Qt::black); // Set pen color
			pen.setWidth(min_side * 0.08f); // Set pen width to control stroke thickness
			painter.setPen(pen);

			painter.drawArc(rect, -1 * ScanButton::current_loading_arc_angle, span_angle);
			break;
		}
		case ScanButton::TextureState::ERROR: {
			/**
			 *     *               *
			 *       *           *
			 *         *       *
			 *           *   *
			 *             *
			 *           *   *
			 *         *       *
			 *       *           *
			 *     *               *
			 */
			float crossSize{ min_side * 0.2f };
			QLineF line1(center - QPointF(crossSize, crossSize), center + QPointF(crossSize, crossSize));
			QLineF line2(center - QPointF(crossSize, -crossSize), center + QPointF(crossSize, -crossSize));

			QPen pen(Qt::SolidLine); // Set pen style to SolidLine
			pen.setColor(Qt::red); // Set pen color
			pen.setWidth(min_side * 0.08f); // Set pen width to control stroke thickness
			painter.setPen(pen);

			painter.drawLine(line1);
			painter.drawLine(line2);
			break;
		}
		default:
			break;
	}
}
