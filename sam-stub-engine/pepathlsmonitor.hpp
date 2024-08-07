/**********************************************************************************/
/*                                                                                */
/* pepathlsmonitor.hpp (stub)                                                     */
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

#ifndef SAM_PE_PATHLS_STUB_MONITOR_HPP
#define SAM_PE_PATHLS_STUB_MONITOR_HPP

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class PEPathlsMonitor {
public:
	PEPathlsMonitor();
	~PEPathlsMonitor() = default;

	void add_pe_pathl(const std::string &pathl);

	bool get_pe_pathl(std::string &pathl_buffer);

	void set_done();

private:
	std::queue<std::string> pathls;

	/**
	 * @brief Each function inside a monitor should satisfy the Mutual Exclusion property which means
	 *        we need this mutex.
	 *
	 */
	std::mutex mtx;

	/**
	 * @brief This condition is nessesary to notify the consumer thread that there is a new pathl to process
	 *        or to wait if there is no pathl to process.
	 *
	 */
	std::condition_variable cv;
	bool done;
}; // class PEPathlsMonitor

#endif // SAM_PE_PATHLS_STUB_MONITOR_HPP
