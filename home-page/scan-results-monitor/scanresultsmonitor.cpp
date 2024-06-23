/**********************************************************************************/
/*                                                                                */
/* scanresultsmonitor.cpp                                                         */
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


#include "scan-results-monitor/scanresultsmonitor.hpp"

#include <iostream>

ScanResultsMonitor::ScanResultsMonitor()
{
    // TODO: Let the engine do the initialization
    ScanResultsMonitor::init();
}

void ScanResultsMonitor::init()
{
    // Disable editing for the entire table
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing for the entire table

    QStringList headers = { "File", "Status" };

    this->setColumnCount(headers.size()); // Set the number of columns
    this->setRowCount(0); // Set the number of rows
    
    this->setHorizontalHeaderLabels(headers);
}

void ScanResultsMonitor::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    ScanResultsMonitor::update_column_widths();
}

void ScanResultsMonitor::update_column_widths()
{
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    int filename_column_width {static_cast<int>(table_width * 0.75f)}; // 75% of table's width for filename column
    int status_column_width {static_cast<int>(table_width * 0.25f)}; // 25% of table's width for status column
    this->setColumnWidth(0, filename_column_width);
    this->setColumnWidth(1, status_column_width);
}

int ScanResultsMonitor::append_new_entry() {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    QTableWidgetItem *filename_item = new QTableWidgetItem();
    QTableWidgetItem *status_item = new QTableWidgetItem();
    this->setItem(row_index, 0, filename_item); // Set the filename in the first column
    this->setItem(row_index, 1, status_item); // Set the status in the second column

    // Ensure the newly added item is visible by scrolling to the bottom
    // this->scrollToBottom();
    
    return row_index;
}

void ScanResultsMonitor::update_entry(const int& row_index, const int& col_index, const std::string& data_buffer, const float& status_prediction) {
    if (row_index < 0 || row_index >= this->rowCount()) {
        std::cerr << "Invalid row index: " << row_index << std::endl;
        return; // Invalid row index
    }

    if (col_index < 0 || col_index >= this->columnCount()) {
        std::cerr << "Invalid column index: " << col_index << std::endl;
        return; // Invalid column index
    }

    QTableWidgetItem *item {this->item(row_index, col_index)};

    if (!item) {
        std::cerr << "Status item not found for row: " << row_index << std::endl;
        return; // Item not found
    }

    item->setText(QString::fromStdString(data_buffer)); // Set the cell text

    // If the status prediction is not set, do not update the background color
    if (col_index != 1 || status_prediction == -1.0f) {
        return;
    }

    // Check https://doc.qt.io/qt-6/qcolor.html#QColor-2 for QColor documentation
    QBrush brush(QColor((int)(status_prediction * 255), (int)((1.0 - status_prediction) * 255), 0, 150)); // Create a brush with the color based on prediction

    // Check https://doc.qt.io/qt-6/qtablewidgetitem.html#setBackground for set background documentation
    item->setBackground(brush);
}
