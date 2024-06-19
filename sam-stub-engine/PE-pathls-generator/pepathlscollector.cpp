/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pepathlscollector.cpp
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
