/**********************************************************************************/
/*                                                                                */
/* pepathlscollector.hpp (stub)                                                   */
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

#ifndef SAM_PE_PATHLS_STUB_COLLECTOR_HPP
#define SAM_PE_PATHLS_STUB_COLLECTOR_HPP

#include <string>
#include <vector>

typedef std::vector<std::string> pathls; // path lines are vector of strings.

class PEPathlsCollector {
public:
	PEPathlsCollector() = default;
	~PEPathlsCollector() = default;

	bool get_target_pathl_extensions(std::vector<std::string> &target_pathl_extensions_buffer);

	bool collect(pathls &pathls_buffer, [[maybe_unused]] const std::string &scan_area);

private:
	bool collect_files([[maybe_unused]] pathls &pathls_buffer, [[maybe_unused]] const std::string &scan_area, [[maybe_unused]] const std::vector<std::string> &target_pathl_extensions);
}; // class PEPathlsCollector

#endif // SAM_PE_PATHLS_STUB_COLLECTOR_HPP
