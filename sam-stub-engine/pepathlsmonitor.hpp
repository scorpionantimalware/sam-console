/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pepathlsmonitor.hpp
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

#ifndef SAM_PE_PATHLS_STUB_MONITOR_HPP
#define SAM_PE_PATHLS_STUB_MONITOR_HPP

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <string>
#include <vector>

class PEPathlsMonitor {
    public:
        PEPathlsMonitor();
        ~PEPathlsMonitor() = default;

        void add_pe_pathl(const std::string& pathl);

        bool get_pe_pathl(std::string& pathl_buffer);

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

