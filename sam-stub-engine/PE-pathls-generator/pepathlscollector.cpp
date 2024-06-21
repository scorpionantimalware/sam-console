/**********************************************************************************/
/*                                                                                */
/* pepathlscollector.cpp (stub)                                                   */
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


#include "pepathlscollector.hpp"

#include <filesystem>

#include <iostream>

bool PEPathlsCollector::get_target_pathl_extensions(std::vector<std::string>& target_pathl_extensions_buffer) {
    bool status {false};
    target_pathl_extensions_buffer.push_back(".exe");
    target_pathl_extensions_buffer.push_back(".dll");
    target_pathl_extensions_buffer.push_back(".lib");
    target_pathl_extensions_buffer.push_back(".msi");
    status = true;
    return status;
}

bool PEPathlsCollector::collect(pathls& pathls_buffer, [[maybe_unused]] const std::string& scan_area) {
    bool status {false};

    // Fill in with dummy data.
    pathls_buffer.push_back("C:/pesamples1/sample1.exe");
    pathls_buffer.push_back("C:/pesamples1/sample2.dll");
    pathls_buffer.push_back("C:/pesamples1/sample3.lib");
    pathls_buffer.push_back("C:/pesamples1/sample4.msi");
    pathls_buffer.push_back("C:/pesamples2/sample5.exe");
    pathls_buffer.push_back("C:/pesamples2/sample6.dll");
    pathls_buffer.push_back("C:/pesamples2/sample7.lib");
    pathls_buffer.push_back("C:/pesamples2/sample8.msi");
    pathls_buffer.push_back("C:/pesamples3/sample9.exe");
    pathls_buffer.push_back("C:/pesamples3/sample10.dll");
    pathls_buffer.push_back("C:/pesamples3/sample11.lib");
    pathls_buffer.push_back("C:/pesamples3/sample12.msi");

    status = true;

    return status;
}


bool PEPathlsCollector::collect_files([[maybe_unused]] pathls& pathls_buffer, [[maybe_unused]] const std::string& scan_area, [[maybe_unused]] const std::vector<std::string>& target_pathl_extensions) {
    bool status {false};

    status = true;

    return status;
}
