#include "scanareascolumn.hpp"

#include <iostream>
#include <QColor>
#include <QBrush>
#include <QHeaderView>
#include <QFileDialog>

#include "samconsolemain.hpp"

ScanAreasColumn::ScanAreasColumn() : scan_areas()
{
    this->setColumnCount(1); // Set the number of columns
    this->setRowCount(0); // Set the number of rows

    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);

    ScanAreasProcessor processor;
    if (!processor.load_or_init(ScanAreasColumn::scan_areas)) {
        std::cerr << "Failed to load scan areas" << std::endl;
    }

    for (const std::string& area : ScanAreasColumn::scan_areas) {
        ScanAreasColumn::add_row(area);
    }
}

ScanAreasColumn::~ScanAreasColumn()
{
    
}

void ScanAreasColumn::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    ScanAreasColumn::update_column_widths();
}

void ScanAreasColumn::on_browse_area_button_clicked()
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
    ScanAreasColumn::add_row(new_area);
}

void ScanAreasColumn::update_column_widths()
{
    int table_width {this->viewport()->width()}; // Use viewport's width to exclude scrollbar width
    this->setColumnWidth(0, table_width);
}

int ScanAreasColumn::add_row(const std::string& area) {
    int row_index {this->rowCount()}; // Get the current row count as the index for the new row
    this->insertRow(row_index);
    QTableWidgetItem *area_item = new QTableWidgetItem(QString::fromStdString(area));
    this->setItem(row_index, 0, area_item); // Set the area in the first column
    return row_index;
}
