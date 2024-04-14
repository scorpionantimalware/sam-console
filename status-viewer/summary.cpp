/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * summary.cpp
 * 
 * Copyright (c) 2024-present Scorpion Anti-malware (see AUTHORS.md).
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include "summary.hpp"

#include <iostream>
#include <QColor>
#include <QBrush>

Summary::Summary()
{
    // Disable editing for the entire table
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing for the entire table

    this->setColumnCount(2); // Set the number of columns
    this->setRowCount(0); // Set the number of rows

    // Set the header labels for the columns
    this->setHorizontalHeaderLabels(QStringList() << "Filename" << "Status");
}

Summary::~Summary()
{
    
}

void Summary::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    Summary::update_column_widths();
}

void Summary::update_column_widths()
{
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    int filename_column_width {static_cast<int>(table_width * 0.75f)}; // 75% of table's width for filename column
    int status_column_width {static_cast<int>(table_width * 0.25f)}; // 25% of table's width for status column
    this->setColumnWidth(0, filename_column_width);
    this->setColumnWidth(1, status_column_width);
}

int Summary::add_row(const std::string& filename) {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    QTableWidgetItem *filename_item = new QTableWidgetItem(QString::fromStdString(filename));
    QTableWidgetItem *status_item = new QTableWidgetItem("Pending");
    this->setItem(row_index, 0, filename_item); // Set the filename in the first column
    this->setItem(row_index, 1, status_item); // Set the status in the second column
    return row_index;
}

void Summary::set_status_for_row(const int& row_index, const std::string& status, const float& prediction) {
    if (row_index < 0 || row_index >= this->rowCount()) {
        std::cerr << "Invalid row index: " << row_index << std::endl;
        return; // Invalid row index
    }

    QTableWidgetItem *status_item {this->item(row_index, 1)}; // Get the item in the second column

    if (!status_item) {
        std::cerr << "Status item not found for row: " << row_index << std::endl;
        return; // Status item not found
    }
        
    status_item->setText(QString::fromStdString(status)); // Set the status text

    // Check https://doc.qt.io/qt-6/qcolor.html#QColor-2 for QColor documentation
    QBrush brush(QColor((int)(prediction * 255), (int)((1.0 - prediction) * 255), 0, 150)); // Create a brush with the color based on prediction

    // Check https://doc.qt.io/qt-6/qtablewidgetitem.html#setBackground for set background documentation
    status_item->setBackground(brush);
}
