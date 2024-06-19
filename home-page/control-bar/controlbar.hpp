/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * controlbar.hpp 
 * 
 * Copyright (c) 2024-present Scorpion Anti-malware (see AUTHORS.md).
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

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
     * @note This is used inside the @c ResultsStreamViewer class.
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
