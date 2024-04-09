#ifndef SUMMARY_H
#define SUMMARY_H

#include <QTableWidget>

class Summary : public QTableWidget
{
public:
    Summary();
    ~Summary();

    int add_row(const std::string& filename);

    void set_status_for_row(const int& row_index, const std::string& status, const float& prediction);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
/**
 * @brief Update the column widths based on the table's width
*/
    void update_column_widths();

};

#endif // SUMMARY_H
