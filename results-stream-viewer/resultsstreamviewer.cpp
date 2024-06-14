/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * resultsstreamviewer.cpp - A class that displays the status of the scan.
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

#include "resultsstreamviewer.hpp"

#include <iostream>

#include "samconsolemain.hpp"

ResultsStreamViewer::ResultsStreamViewer()
{
    ResultsStreamViewer::init();
}

ResultsStreamViewer::~ResultsStreamViewer()
{
}

void ResultsStreamViewer::init()
{
    // Disable editing for the entire table
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing for the entire table

    this->setColumnCount(2); // Set the number of columns
    this->setRowCount(0); // Set the number of rows

    // Set the header labels for the columns
    this->setHorizontalHeaderLabels(QStringList() << "Filename" << "Status");
}

void ResultsStreamViewer::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    ResultsStreamViewer::update_column_widths();
}

void ResultsStreamViewer::update_column_widths()
{
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    int filename_column_width {static_cast<int>(table_width * 0.75f)}; // 75% of table's width for filename column
    int status_column_width {static_cast<int>(table_width * 0.25f)}; // 25% of table's width for status column
    this->setColumnWidth(0, filename_column_width);
    this->setColumnWidth(1, status_column_width);
}

int ResultsStreamViewer::add_row(const std::string& filename) {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    QTableWidgetItem *filename_item = new QTableWidgetItem(QString::fromStdString(filename));
    QTableWidgetItem *status_item = new QTableWidgetItem("Pending");
    this->setItem(row_index, 0, filename_item); // Set the filename in the first column
    this->setItem(row_index, 1, status_item); // Set the status in the second column
    return row_index;
}

void ResultsStreamViewer::set_status_for_row(const int& row_index, const std::string& status, const float& prediction) {
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

void ResultsStreamViewer::on_scan_fire()
{
    std::cout << "Scan fired" << std::endl;
}

void ResultsStreamViewer::on_scan_complete()
{
    std::cout << "Scan complete" << std::endl;
}

int ResultsStreamViewer::on_new_file(const std::string& filename)
{
    std::cout << "New file: " << filename << std::endl;
    return ResultsStreamViewer::add_row(filename);
}

void ResultsStreamViewer::on_status(const int& row_index, const float& prediction)
{
    std::cout << "Status for row " << row_index << ": " << prediction << std::endl;

    /*
        -1.0 is the default value for the buffer that is being sent to the model.
        If the model is not able to predict the file, it will not fill the buffer.
    */
    std::string status {prediction == -1.0f ? "Failed" : prediction > 0.5f ? "Malware" : "Benign"};
    ResultsStreamViewer::set_status_for_row(row_index, status, prediction);
}

void ResultsStreamViewer::on_scan_button_clicked()
{
    // this->setEnabled(true);
    std::cout << "Scanning..." << std::endl;
    sam_engine::sam_engine_scan();
}
