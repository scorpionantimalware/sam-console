#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>

#include "samconsolemain.hpp"

#include "controlbar.hpp"
#include "statusviewer.hpp"
#include "scanareascontroller.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ControlBar* get_control_bar();
    StatusViewer* get_status_viewer();

private slots:
    void on_scan_areas_controller_button_clicked();

private:
    QVBoxLayout *main_layout;

    ControlBar* control_bar;
    StatusViewer* status_viewer;

    ScanAreasController *scan_areas_controller;
};

#endif // MAIN_WINDOW_H
