/**********************************************************************************/
/*                                                                                */
/* controlbar.hpp                                                                 */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware is a free Open Source AI-powered Anti-malware         */
/*    framework for Researchers.                                                  */
/*                                                                                */
/*    Copyright (c) 2024-present  (see AUTHORS.md).                               */
/*                                                                                */
/*    This program is free software: you can redistribute it and/or modify        */
/*    it under the terms of the GNU General Public License as published by        */
/*    the Free Software Foundation, either version 3 of the License, or           */
/*    (at your option) any later version.                                         */
/*                                                                                */
/*    This program is distributed in the hope that it will be useful,             */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of              */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               */
/*    GNU General Public License for more details.                                */
/*                                                                                */
/*    You should have received a copy of the GNU General Public License           */
/*    along with this program.  If not, see <https://www.gnu.org/licenses/>.      */
/*                                                                                */
/**********************************************************************************/


#ifndef SAM_CONTROL_BAR_HPP
#define SAM_CONTROL_BAR_HPP

#include <QWidget>
#include <QHBoxLayout>

#include "control-bar/scanbutton.hpp"
#include "control-bar/stopbutton.hpp"
#include "control-bar/pausebutton.hpp"
#include "control-bar/resumebutton.hpp"
#include "control-bar/scanareascontrollerbutton.hpp"

#include "samconsolemain.hpp"

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    ControlBar(QWidget *parent = nullptr);
    ~ControlBar();

signals:
    /**
     * @brief Signal emitted when the scan button is clicked.
     * 
     * @note This is used inside the @c ScanResultsMonitor class.
     * 
     * @see @c mainwindow.hpp
     * @see @c MainWindow::on_scan_button_clicked()
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
     * @brief Signal emitted when the resume button is clicked.
    */
    void resume_button_clicked();

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
     * @brief Slot to resume the scan.
    */
    void resume_scan();

    /**
     * @brief Slot to show the scan areas controller.
    */
    void open_scan_areas_controller();

private:
    QHBoxLayout *main_layout;

    ScanButton *scan_button;
    StopButton *stop_button;
    PauseButton *pause_button;
    ResumeButton *resume_button;
    ScanAreasControllerButton *scan_areas_controller_button;
};

#endif // SAM_CONTROL_BAR_HPP
