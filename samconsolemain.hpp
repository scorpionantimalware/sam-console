/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * samconsolemain.hpp
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

#ifndef SAM_CONSOLE_MAIN_HPP
#define SAM_CONSOLE_MAIN_HPP

// If the real engine is active, include the real engine.
#ifdef SAM_ENGINE_ACTIVE
#ifdef SAM_DUMMY_ENGINE_ACTIVE // If both engines are active, throw an error.
#error "Both real and dummy engines are active"
#else // If only the real engine is active, include the real engine.
#include "samengine.hpp"
#include "scanareasprocessor.hpp"
#endif // SAM_DUMMY_ENGINE_ACTIVE
#elif SAM_DUMMY_ENGINE_ACTIVE // If the dummy engine is active, include the dummy engine.
#include "samdummyengine.hpp"
#include "scanareasdummyprocessor.hpp"

/**
 * @brief The main funtion to scan is different accross the dummy and real 
 *        engines. This is the dummy engine's main function.
 * 
 */
#define sam_engine_scan sam_dummy_engine_scan

/**
 * @brief The namespace is different accross the dummy and real engines. This
 *        is the dummy engine's namespace.
 * 
 */
#define sam_engine sam_dummy_engine 

typedef ScanAreasDummyProcessor ScanAreasProcessor;
#else // If no engine is active, throw an error.
#error "No engine found"
#endif // SAM_ENGINE_ACTIVE

#ifndef SAM_ORG_NAME
#error "No organization name defined"
#endif // SAM_ORG_NAME

#ifndef SAM_CONSOLE_PROJECT_NAME
#error "No project name defined"
#endif // SAM_CONSOLE_PROJECT_NAME

#ifndef SAM_CONSOLE_PROJECT_VERSION
#error "No project version defined"
#endif // SAM_CONSOLE_PROJECT_VERSION

#include "mainwindow.hpp"

int main(int argc, char **argv);

void scan_fire_callback();

void scan_complete_callback();

int new_file_callback(const std::string& filename);

void status_callback(const int& row_index, const float& prediction);

#endif // SAM_CONSOLE_MAIN_HPP
