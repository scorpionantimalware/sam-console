/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanareasdummyprocessor.hpp - A class that represents the scan areas dummy processor.
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

#ifndef SAM_SCAN_AREAS_DUMMY_PROCESSOR_H
#define SAM_SCAN_AREAS_DUMMY_PROCESSOR_H

#include <string>
#include <vector>

typedef std::vector<std::string> pathls; // path lines are vector of strings.

const std::string SCAN_AREAS_FILENAME {"scanareasprocessor_output.pathl"};

class ScanAreasDummyProcessor {
public:
    ScanAreasDummyProcessor() = default;
    ~ScanAreasDummyProcessor() = default;

    bool load_or_init(pathls& scan_areas);

    bool add_area([[maybe_unused]] const std::string& area);
};

#endif // SAM_SCAN_AREAS_DUMMY_PROCESSOR_H
