/**********************************************************************************/
/*                                                                                */
/* pepathlsmonitor.cpp (stub)                                                     */
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

#include "pepathlsmonitor.hpp"

PEPathlsMonitor::PEPathlsMonitor() :
		done(false) {}

void PEPathlsMonitor::add_pe_pathl(const std::string &pathl) {
	std::unique_lock<std::mutex> lock(PEPathlsMonitor::mtx); // Ensure Mutual Exclusion
	PEPathlsMonitor::pathls.push(pathl);
	PEPathlsMonitor::cv.notify_one();
}

bool PEPathlsMonitor::get_pe_pathl(std::string &pathl_buffer) {
	std::unique_lock<std::mutex> lock(PEPathlsMonitor::mtx); // Ensure Mutual Exclusion

	bool status{ false };

	while (PEPathlsMonitor::pathls.empty() && !PEPathlsMonitor::done) {
		PEPathlsMonitor::cv.wait(lock);
	}

	if (PEPathlsMonitor::pathls.empty()) {
		return status;
	}

	pathl_buffer = PEPathlsMonitor::pathls.front();
	PEPathlsMonitor::pathls.pop();

	status = true;

	return status;
}

void PEPathlsMonitor::set_done() {
	std::unique_lock<std::mutex> lock(PEPathlsMonitor::mtx); // Ensure Mutual Exclusion
	PEPathlsMonitor::done = true;
	PEPathlsMonitor::cv.notify_all();
}
