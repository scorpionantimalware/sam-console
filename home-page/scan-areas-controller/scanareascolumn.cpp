/**********************************************************************************/
/*                                                                                */
/* scanareascolumn.cpp                                                            */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware is a free Open Source AI-powered Anti-malware         */
/*    framework for Researchers.                                                  */
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


#include "scan-areas-controller/scanareascolumn.hpp"

#include <iostream>
#include <QColor>
#include <QBrush>
#include <QHeaderView>
#include <QFileDialog>

#include "samconsolemain.hpp"

ScanAreasColumn::ScanAreasColumn() {
    ScanAreasColumn::init();

    ScanAreasProcessor processor;
    if (!processor.load_or_init(ScanAreasColumn::scan_areas)) {
        std::cerr << "Failed to load scan areas" << std::endl;
    }

    for (const std::string& area : ScanAreasColumn::scan_areas) {
        ScanAreasColumn::append_new_entry(area);
    }
}

void ScanAreasColumn::init()
{
    this->setColumnCount(1); // Set the number of columns
    this->setRowCount(0); // Set the number of rows

    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
}

void ScanAreasColumn::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    ScanAreasColumn::update_column_widths();
}

void ScanAreasColumn::on_area_browse_button_clicked()
{
    // Open the file explorer to select a directory
    std::string new_area { QFileDialog::getExistingDirectory(nullptr, "Select an area to scan", QDir::homePath()).toStdString() };

    // Check if the new_area is empty
    if (new_area.empty()) {
        return;
    }

    ScanAreasProcessor processor;
    processor.add_area(new_area);
    ScanAreasColumn::scan_areas.push_back(new_area);
    ScanAreasColumn::append_new_entry(new_area);
}

void ScanAreasColumn::update_column_widths()
{
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    this->setColumnWidth(0, table_width);
}

int ScanAreasColumn::append_new_entry(const std::string& area) {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    QTableWidgetItem *area_item = new QTableWidgetItem(QString::fromStdString(area));
    this->setItem(row_index, 0, area_item); // Set the area in the first column
    return row_index;
}
