#ifndef STATUSVIEWER_H
#define STATUSVIEWER_H

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

public slots:
    void on_scan_clicked();

private:
    QVBoxLayout *main_layout;

    QProgressBar *progress_bar;
    Summary *summary;
};

#endif // STATUSVIEWER_H
