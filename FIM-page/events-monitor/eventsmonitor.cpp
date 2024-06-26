/**********************************************************************************/
/*                                                                                */
/* eventsmonitor.cpp                                                              */
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


#include "events-monitor/eventsmonitor.hpp"

#include <iostream>

EventsMonitor::EventsMonitor()
{
    // TODO: Let the engine do the initialization
    EventsMonitor::init();
}

void EventsMonitor::init() {
    // Disable editing for the entire table
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing for the entire table

    QStringList headers {{ "Filename", "Action", "New Hash", "Old Hash", "Time" }};

    this->setColumnCount(headers.size()); // Set the number of columns
    this->setRowCount(0); // Set the number of rows
    
    this->setHorizontalHeaderLabels(headers);
}

void EventsMonitor::resizeEvent(QResizeEvent *event) {
    QTableWidget::resizeEvent(event);
    EventsMonitor::update_column_widths();
}

void EventsMonitor::update_column_widths() {
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    int filename_column_width {static_cast<int>(table_width * 0.2f)};
    int action_column_width {static_cast<int>(table_width * 0.1f)};
    int new_hash_column_width {static_cast<int>(table_width * 0.3f)};
    int old_hash_column_width {static_cast<int>(table_width * 0.3f)};
    int time_column_width {static_cast<int>(table_width * 0.1f)};
    this->setColumnWidth(0, filename_column_width);
    this->setColumnWidth(1, action_column_width);
    this->setColumnWidth(2, new_hash_column_width);
    this->setColumnWidth(3, old_hash_column_width);
    this->setColumnWidth(4, time_column_width);
}

int EventsMonitor::append_new_entry() {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    QTableWidgetItem *filename_item = new QTableWidgetItem();
    QTableWidgetItem *action_item = new QTableWidgetItem();
    QTableWidgetItem *new_hash_item = new QTableWidgetItem();
    QTableWidgetItem *old_hash_item = new QTableWidgetItem();
    QTableWidgetItem *time_item = new QTableWidgetItem();
    this->setItem(row_index, 0, filename_item); // Set the filename in the first column
    this->setItem(row_index, 1, action_item); // Set the action in the second column
    this->setItem(row_index, 2, new_hash_item); // Set the new hash in the third column
    this->setItem(row_index, 3, old_hash_item); // Set the old hash in the fourth column
    this->setItem(row_index, 4, time_item); // Set the time in the fifth column
    
    return row_index;
}

void EventsMonitor::update_entry(const int& row_index, const int& col_index, const std::string& data_buffer) const {
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
        std::cerr << "Item item not found for row: " << row_index << std::endl;
        return; // Item not found
    }

    item->setText(QString::fromStdString(data_buffer)); // Set the cell text
}
