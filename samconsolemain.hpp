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
#ifdef SAM_ENGINE_ACTIVE /*     Scorpion Anti-malware Engine Configuration     */

#ifdef SAM_STUB_ENGINE_ACTIVE // If both engines are active, throw an error.
#error "Both real and stub engines are active"
#else // If only the real engine is active, include the real engine.
#include "samengine.hpp"
#include "scanareasprocessor.hpp"
#endif // SAM_STUB_ENGINE_ACTIVE

// If the stub engine is active, include the stub engine.
#elif SAM_STUB_ENGINE_ACTIVE /*     Scorpion Anti-malware Stub Engine Configuration     */

#ifdef SAM_ENGINE_ACTIVE // If both engines are active, throw an error.
#error "Both real and stub engines are active"
#else // If only the real engine is active, include the real engine.
#include "samengine.hpp"
#include "scanareasprocessor.hpp"
#endif // SAM_STUB_ENGINE_ACTIVE

// If no engine is active, throw an error.
#else /*     No Engine Configuration     */
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

#ifndef SAM_CONSOLE_ROOTDIR
#error "No root directory defined"
#endif // SAM_CONSOLE_ROOTDIR

extern sam_engine::SAMEngine *engine;

int main(int argc, char **argv);

namespace sam_callbacks {

	int add_new_file_callback();
	void update_new_file_callback(const int& row_index, const int& col_index, const std::string& data_buffer, const float& status_prediction = -1.0f);
	void scanner_state_change_callback([[maybe_unused]] const sam_engine::SAMScanner::State& scanner_state);
	void update_engine_status_callback(const std::string& status_message, const sam_engine::SAMEngine::StatusMessageType& type);

} // namespace sam_callbacks

#endif // SAM_CONSOLE_MAIN_HPP
