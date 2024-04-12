#ifndef CONTROL_BAR_H
#define CONTROL_BAR_H

#include <QWidget>
#include <QHBoxLayout>

#include "scanbutton.hpp"
#include "stopbutton.hpp"
#include "pausebutton.hpp"
#include "scanareascontrollerbutton.hpp"

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    ControlBar();
    ~ControlBar();

signals:
    /**
     * @brief Signal emitted when the scan button is clicked.
     * 
     * @note This is used inside the @c StatusViewer class.
     * 
     * @see @c status-viewer/statusviewer.hpp
     * @see @c StatusViewer::on_scan_button_clicked
    */
    void scan_button_clicked();

    /**
     * @brief Signal emitted when the stop button is clicked.
    */
    void stop_button_clicked();

    /**
     * @brief Signal emitted when the pause button is clicked.
    */
    void pause_button_clicked();

    /**
     * @brief Signal emitted when the scan areas controller button is clicked.
     * 
     * @note This is used inside the @c MainWindow class and opens
     *       the @c ScanAreasController class.
     * 
     * @see @c scan-areas-controller/scanareascontroller.hpp
     * @see @c mainwindow.hpp
     * @see @c MainWindow::on_scan_areas_controller_button_clicked
    */
    void scan_areas_controller_button_clicked();

private slots:
    /**
     * @brief Slot to start the scan.
    */
    void start_scan();

    /**
     * @brief Slot to stop the scan.
    */
    void stop_scan();

    /**
     * @brief Slot to pause the scan.
    */
    void pause_scan();

    /**
     * @brief Slot to show the scan areas controller.
    */
    void show_scan_areas_controller();

private:
    QHBoxLayout *main_layout;

    ScanButton *scan_button;
    StopButton *stop_button;
    PauseButton *pause_button;
    ScanAreasControllerButton *scan_areas_controller_button;
    
};

#endif // CONTROL_BAR_H
