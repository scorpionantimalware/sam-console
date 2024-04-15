#ifndef SAM_MAIN_WINDOW_HPP
#define SAM_MAIN_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>

#include "samconsolemain.hpp"

#include "controlbar.hpp"
#include "resultsstreamviewer.hpp"
#include "scanareascontroller.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ControlBar* get_control_bar();
    ResultsStreamViewer* get_results_stream_viewer();

private slots:
    void on_scan_areas_controller_button_clicked();

private:
    QVBoxLayout *main_layout;

    ControlBar* control_bar;
    ResultsStreamViewer* results_stream_viewer;

    ScanAreasController *scan_areas_controller;
};

#endif // SAM_MAIN_WINDOW_HPP
