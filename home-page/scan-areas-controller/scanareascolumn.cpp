/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanareascolumn.cpp
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
