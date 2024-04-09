#include "summary.hpp"

#include <iostream>

Summary::Summary()
{
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
    int table_width = viewport()->width(); // Use viewport's width to exclude scrollbar width
    int filename_column_width = table_width * 0.75; // 75% of table's width for filename column
    int status_column_width = table_width * 0.25; // 25% of table's width for status column
    setColumnWidth(0, filename_column_width);
    setColumnWidth(1, status_column_width);
}

int Summary::add_row(const std::string& filename) {
    int row_index = this->rowCount(); // Get the current row count as the index for the new row
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

    QTableWidgetItem *status_item = this->item(row_index, 1); // Get the item in the second column

    if (!status_item) {
        std::cerr << "Status item not found for row: " << row_index << std::endl;
        return; // Status item not found
    }
        
    status_item->setText(QString::fromStdString(status)); // Set the status text
    status_item->setBackground(QColor(prediction * 255, (1.0 - prediction) * 255, 0.0, 1.0));
}
