/**********************************************************************************/
/*                                                                                */
/* homepage.hpp                                                                   */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware Console is a free Open Source Qt-powered frontend     */
/*    framework for SAM Engine.                                                   */
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

#ifndef SAM_HOME_PAGE_HPP
#define SAM_HOME_PAGE_HPP

#include <QVBoxLayout>
#include <QWidget>

#include "control-bar/controlbar.hpp"
#include "engine-status-monitor/enginestatusmonitor.hpp"
#include "scan-areas-controller/scanareascontroller.hpp"
#include "scan-results-monitor/scanresultsmonitor.hpp"

#include "samconsolesplash.hpp"

class HomePage : public QWidget {
	Q_OBJECT

public:
	explicit HomePage(QWidget *parent = nullptr);
	~HomePage();

	ControlBar *get_control_bar_p() const;
	EngineStatusMonitor *get_engine_status_monitor_p() const;
	ScanResultsMonitor *get_scan_results_monitor_p() const;

private slots:
	void on_scan_button_clicked() const;
	void on_stop_button_clicked() const;
	void on_pause_button_clicked() const;
	void on_resume_button_clicked() const;
	void on_scan_areas_controller_button_clicked();

private:
	SAMConsoleSplash *splash_screen;

	QVBoxLayout *main_layout;

	ControlBar *control_bar;
	EngineStatusMonitor *engine_status_monitor;
	ScanResultsMonitor *scan_results_monitor;

	ScanAreasController *scan_areas_controller;
};

#endif // SAM_HOME_PAGE_HPP
