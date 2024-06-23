/**********************************************************************************/
/*                                                                                */
/* samconsolemain.hpp                                                             */
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

	void fim_new_event_callback();

} // namespace sam_callbacks

#endif // SAM_CONSOLE_MAIN_HPP
