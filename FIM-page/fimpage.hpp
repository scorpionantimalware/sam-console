/**********************************************************************************/
/*                                                                                */
/* fimpage.hpp                                                                    */
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

#ifndef SAM_FIM_PAGE_HPP
#define SAM_FIM_PAGE_HPP

#include <QVBoxLayout>
#include <QWidget>

#include "events-monitor/eventsmonitor.hpp"

class FIMPage : public QWidget {
	Q_OBJECT

public:
	explicit FIMPage(QWidget *parent = nullptr);
	~FIMPage();

	EventsMonitor *get_events_monitor_p() const;

private:
	QVBoxLayout *main_layout;

	EventsMonitor *events_monitor;
};

#endif // SAM_FIM_PAGE_HPP
