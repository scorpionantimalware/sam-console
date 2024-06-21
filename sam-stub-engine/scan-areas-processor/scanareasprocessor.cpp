/**********************************************************************************/
/*                                                                                */
/* scanareasprocessor.cpp (stub)                                                  */
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


#include "scanareasprocessor.hpp"

bool ScanAreasProcessor::load_or_init(pathls& scan_areas) {
    bool status {false};

    scan_areas.push_back("C:/pesamples1");
    scan_areas.push_back("C:/pesamples2");
    scan_areas.push_back("C:/pesamples3");

    status = true;

    return status;
}

bool ScanAreasProcessor::add_area([[maybe_unused]] const std::string& area) {
    bool status {false};

    status = true;

    return status;
}
