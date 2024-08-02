/**********************************************************************************/
/*                                                                                */
/* resumebutton.cpp                                                               */
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

#include "control-bar/resumebutton.hpp"

ResumeButton::ResumeButton() {
	this->setFixedSize(100, 100);
}

void ResumeButton::paintEvent(QPaintEvent *event) {
	QPushButton::paintEvent(event);

	QPainter painter = QPainter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int w{ this->width() };
	int h{ this->height() };

	float min_side{ (float)qMin(w, h) };

	QPointF center{ w * 0.5f, h * 0.5f };

	float vc_length{ min_side * 0.25f }; // Length from each triangle's vertex to the center of the widget

	// Calculate the vertices of the triangle based on the center of the widget
	QPointF top_v{ center + QPointF(vc_length, 0) };
	QPointF bottom_left_v{ center - QPointF(vc_length, vc_length) };
	QPointF bottom_right_v{ center - QPointF(vc_length, -vc_length) };

	// Draw the triangle
	painter.setBrush(Qt::blue);
	painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
	painter.drawPolygon(QPolygonF() << top_v << bottom_left_v << bottom_right_v);
}
