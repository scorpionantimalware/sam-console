/**********************************************************************************/
/*                                                                                */
/* pausebutton.cpp                                                                */
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

#include "control-bar/pausebutton.hpp"

#include <QWidget>

PauseButton::PauseButton() {
	this->setFixedSize(100, 100);
}

void PauseButton::paintEvent(QPaintEvent *event) {
	QPushButton::paintEvent(event);

	QPainter painter = QPainter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int w{ this->width() };
	int h{ this->height() };

	float min_side{ (float)qMin(w, h) };

	// Use Multiplication instead of Division as it is faster
	QPointF center{ w * 0.5f, h * 0.5f };

	float max_height{ min_side * 0.18f }; // Max height of the pause symbol from the center.
	float separation{ min_side * 0.15f };
	float pen_width{ separation };

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
