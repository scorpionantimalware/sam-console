#ifndef SCAN_AREAS_COLUMN_H
#define SCAN_AREAS_COLUMN_H

#include <QTableWidget>
#include <vector>
#include <string>

class ScanAreasColumn : public QTableWidget
{
public:
    ScanAreasColumn();
    ~ScanAreasColumn();

    int add_row(const std::string& area);

public slots:
    void on_browse_area_button_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    std::vector<std::string> scan_areas;

/**
 * @brief Update the column widths based on the table's width
*/
    void update_column_widths();

};

#endif // SCAN_AREAS_COLUMN_H
