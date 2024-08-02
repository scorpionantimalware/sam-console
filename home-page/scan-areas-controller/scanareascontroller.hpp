/**********************************************************************************/
/*                                                                                */
/* scanareascolumn.cpp                                                            */
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

#ifndef SAM_SCAN_AREAS_CONTROLLER_HPP
#define SAM_SCAN_AREAS_CONTROLLER_HPP

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "scan-areas-controller/scanareascolumn.hpp"

class ScanAreasController : public QWidget {
	Q_OBJECT

public:
	explicit ScanAreasController(QWidget *parent = nullptr);
	~ScanAreasController();

signals:
	/**
	 * @brief Signal emitted when the new area button is clicked.
	 */
	void new_area_add_button_clicked() const;

	/**
	 * @brief Signal emitted when the edit area button is clicked.
	 */
	void area_edit_button_clicked() const;

	/**
	 * @brief Signal emitted when the browse area button is clicked.
	 *
	 * @note This is used inside the @c ScanAreasColumn class. It adds
	 *       a new area to the list of scan areas.
	 *
	 * @note It calls the @c ScanAreasProcessor::add_area method.
	 *
	 * @see @c scan-areas-processor/scanareasprocessor.hpp
	 * @see @c ScanAreasColumn::on_browse_area_button_clicked
	 */
	void area_browse_button_clicked() const;

	/**
	 * @brief Signal emitted when the delete area button is clicked.
	 */
	void area_delete_button_clicked() const;

private slots:
	/**
	 * @brief Slot to add a new area.
	 */
	void add_new_area() const;

	/**
	 * @brief Slot to edit an area.
	 */
	void edit_existing_area() const;

	/**
	 * @brief Slot to browse an area.
	 */
	void browse_filesystem_for_area() const;

	/**
	 * @brief Slot to delete an area.
	 */
	void delete_existing_area() const;

private:
	QHBoxLayout *main_layout;

	ScanAreasColumn *scan_areas_column;

	QVBoxLayout *buttons_layout;

	QPushButton *add_new_button;
	QPushButton *edit_button;
	QPushButton *browse_button;
	QPushButton *delete_button;
};

#endif // SAM_SCAN_AREAS_CONTROLLER_HPP
