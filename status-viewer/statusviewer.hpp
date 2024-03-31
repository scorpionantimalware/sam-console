#ifndef STATUSVIEWER_H
#define STATUSVIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class StatusViewer : public QWidget
{
public:
    StatusViewer();
    ~StatusViewer();

public slots:
    void on_scan_clicked();

private:
    QVBoxLayout *main_layout;
};

#endif // STATUSVIEWER_H
