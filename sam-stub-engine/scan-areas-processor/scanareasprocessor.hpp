/**********************************************************************************/
/*                                                                                */
/* scanareasprocessor.hpp (stub)                                                  */
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

#ifndef SAM_SCAN_AREAS_STUB_PROCESSOR_HPP
#define SAM_SCAN_AREAS_STUB_PROCESSOR_HPP

#include <string>
#include <vector>

typedef std::vector<std::string> pathls; // path lines are vector of strings.

const std::string SCAN_AREAS_FILENAME{ "scanareasprocessor_output.pathl" };

class ScanAreasProcessor {
public:
	ScanAreasProcessor() = default;
	~ScanAreasProcessor() = default;

	bool load_or_init(pathls &scan_areas);

	bool add_area([[maybe_unused]] const std::string &area);
};

#endif // SAM_SCAN_AREAS_STUB_PROCESSOR_HPP
