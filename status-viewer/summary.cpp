#include "summary.h"

Summary::Summary()
{
    setColumnCount(3); // Set the number of columns
    setRowCount(3); // Set the number of rows

    // Set the header labels for the columns
    setHorizontalHeaderLabels(QStringList() << "Column 1" << "Column 2" << "Column 3");

    // Set the header labels for the rows (using QTableWidgetItem)
    QTableWidgetItem *headerItem1 = new QTableWidgetItem("Row 1");
    QTableWidgetItem *headerItem2 = new QTableWidgetItem("Row 2");
    QTableWidgetItem *headerItem3 = new QTableWidgetItem("Row 3");
    setVerticalHeaderItem(0, headerItem1);
    setVerticalHeaderItem(1, headerItem2);
    setVerticalHeaderItem(2, headerItem3);

    // Set data for cells in the table
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(QString("Row %1, Col %2").arg(row + 1).arg(col + 1));
            setItem(row, col, item);
        }
    }
}

Summary::~Summary()
{
    
}
