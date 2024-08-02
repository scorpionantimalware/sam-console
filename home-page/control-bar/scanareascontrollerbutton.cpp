/**********************************************************************************/
/*                                                                                */
/* scanareascontrollerbutton.cpp                                                  */
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

#include "control-bar/scanareascontrollerbutton.hpp"

#include <QWidget>
#include <cmath>

ScanAreasControllerButton::ScanAreasControllerButton() {
	this->setFixedSize(150, 100);
}

void ScanAreasControllerButton::paintEvent(QPaintEvent *event) {
	QPushButton::paintEvent(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int w{ this->width() };
	int h{ this->height() };

	float min_side{ (float)qMin(w, h) };

	QPointF center{ w * 0.5f, h * 0.5f };

	QPen pen(Qt::SolidLine); // Set pen style to SolidLine
	pen.setColor(Qt::black); // Set pen color
	pen.setWidth(min_side * 0.08f); // Set pen width to control stroke thickness
	painter.setPen(pen);

	// Draw the lens.
	QPointF lens_circle_center{ center - QPointF(min_side * 0.1f, min_side * 0.1f) };
	float lens_circle_radius{ min_side * 0.22f };
	painter.drawEllipse(lens_circle_center, lens_circle_radius, lens_circle_radius);

	// Draw the line.

	/*
		Here we start from the circle boundary (we get the circle boundary by adding the radius
		on the lens' center toward -45 direction).
	*/
	float direction{ qDegreesToRadians(45.0f) };
	QPointF line_start{ lens_circle_center + QPointF(lens_circle_radius * cos(direction), lens_circle_radius * sin(direction)) };

	/*
		Here we add the radius to the line start point (toward -45 direction) to get the
		line end point.
	*/
	QPointF line_end{ line_start + QPointF(lens_circle_radius * cos(direction), lens_circle_radius * sin(direction)) };
	painter.drawLine(line_start, line_end);
}
