/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pepathlscollector.hpp
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

#ifndef SAM_PE_PATHLS_STUB_COLLECTOR_HPP
#define SAM_PE_PATHLS_STUB_COLLECTOR_HPP

#include <vector>
#include <string>

typedef std::vector<std::string> pathls; // path lines are vector of strings.

class PEPathlsCollector {
    public:
        PEPathlsCollector() = default;
        ~PEPathlsCollector() = default;

        bool get_target_pathl_extensions(std::vector<std::string>& target_pathl_extensions_buffer);

        bool collect(pathls& pathls_buffer, const std::string& scan_area);

    private:
        bool collect_files(pathls& pathls_buffer, const std::string& scan_area, const std::vector<std::string>& target_pathl_extensions);
}; // class PEPathlsCollector

#endif // SAM_PE_PATHLS_STUB_COLLECTOR_HPP
