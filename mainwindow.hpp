/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * mainwindow.hpp
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

#ifndef SAM_MAIN_WINDOW_HPP
#define SAM_MAIN_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>

#include "samengine.hpp"

#include "samconsolesplash.hpp"
#include "controlbar.hpp"
#include "statusbuiltinterminal.hpp"
#include "resultsstreamviewer.hpp"
#include "scanareascontroller.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ControlBar* get_control_bar();
    StatusBuiltinTerminal* get_status_builtin_terminal();
    ResultsStreamViewer* get_results_stream_viewer();

private slots:
    void on_scan_button_clicked();
    void on_stop_button_clicked();
    void on_pause_button_clicked();
    void on_scan_areas_controller_button_clicked();

private:
    SAMConsoleSplash *splash_screen;

    QVBoxLayout *main_layout;

    ControlBar* control_bar;
    StatusBuiltinTerminal* status_builtin_terminal;
    ResultsStreamViewer* results_stream_viewer;

    ScanAreasController *scan_areas_controller;

    void show_main_ui();
};

#endif // SAM_MAIN_WINDOW_HPP
