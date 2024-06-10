/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * samdummyengine.hpp
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

#ifndef SAM_DUMMY_ENGINE_HPP
#define SAM_DUMMY_ENGINE_HPP

#include <thread>
#include <mutex>

/*
  When the engine starts scanning, it will call this callback to notify the GUI.
*/
typedef void (*ScanFireCallback_t)(void);

/*
  When the engine finishes scanning, it will call this callback to notify the GUI.
*/
typedef void (*ScanCompleteCallback_t)(void);

/*
  When the engine start scanning a new file, it will call this callback
  with the new file's name to notify the GUI.
*/
typedef int (*NewFileCallback_t)(const std::string&);

/*
  When the engine finishes scanning a file, it will call this callback
  with the file's ID and the prediction to notify the GUI.
*/
typedef void (*StatusCallback_t)(const int&, const float&);

void hook_scan_fire_callback(ScanFireCallback_t callback);
void hook_scan_complete_callback(ScanCompleteCallback_t callback);
void hook_new_file_callback(NewFileCallback_t callback);
void hook_status_callback(StatusCallback_t callback);

bool sam_dummy_engine_scan();

#endif // SAM_DUMMY_ENGINE_HPP
