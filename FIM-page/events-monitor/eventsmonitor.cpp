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

void EventsMonitor::init()
{
    // Disable editing for the entire table
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing for the entire table

    this->setColumnCount(2); // Set the number of columns
    this->setRowCount(0); // Set the number of rows
    
    // QStringList headers = { };
    // this->setHorizontalHeaderLabels(headers);
}

void EventsMonitor::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    EventsMonitor::update_column_widths();
}

void EventsMonitor::update_column_widths()
{
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    int filename_column_width {static_cast<int>(table_width * 0.75f)}; // 75% of table's width for filename column
    int status_column_width {static_cast<int>(table_width * 0.25f)}; // 25% of table's width for status column
    this->setColumnWidth(0, filename_column_width);
    this->setColumnWidth(1, status_column_width);
}

int EventsMonitor::append_new_entry() {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    
    return row_index;
}

void EventsMonitor::update_entry(const int& row_index, const int& col_index, const std::string& data_buffer, const float& status_prediction) {
    
}
