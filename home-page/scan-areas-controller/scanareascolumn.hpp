/**********************************************************************************/
/*                                                                                */
/* scanareascolumn.hpp                                                            */
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

#ifndef SAM_SCAN_AREAS_COLUMN_HPP
#define SAM_SCAN_AREAS_COLUMN_HPP

#include <QTableWidget>
#include <string>
#include <vector>

class ScanAreasColumn : public QTableWidget {
public:
	ScanAreasColumn();

	int append_new_entry(const std::string &area);

public slots:
	void on_area_browse_button_clicked();

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	std::vector<std::string> scan_areas;

	void init();

	/**
	 * @brief Update the column widths based on the table's width
	 */
	void update_column_widths();
};

#endif // SAM_SCAN_AREAS_COLUMN_HPP
