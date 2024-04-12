#ifndef STATUS_VIEWER_H
#define STATUS_VIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "summary.hpp"
#include <QProgressBar>

class StatusViewer : public QWidget
{
public:
    StatusViewer();
    ~StatusViewer();

    void on_scan_fire();
    void on_scan_complete();
    int on_new_file(const std::string& filename);
    void on_status(const int& row_index, const float& prediction);

public slots:
    void on_scan_button_clicked();

private:
    QVBoxLayout *main_layout;

    QProgressBar *progress_bar;
    Summary *summary;
};

#endif // STATUS_VIEWER_H
