/**********************************************************************************/
/*                                                                                */
/* samengine.hpp (stub)                                                           */
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

#ifndef SAM_STUB_ENGINE_HPP
#define SAM_STUB_ENGINE_HPP

#include <mutex>
#include <thread>

#include <condition_variable>

#include <atomic>

#include "pepathlsmonitor.hpp"
#include "scananalyzer.hpp"

namespace sam_engine {
class SAMScanner;

class SAMEngine {
public:
	enum class StatusMessageType {
		INFO,
		WARNING,
		ERROR
	};

	SAMEngine();
	~SAMEngine();

	/**
	 * @brief This function will start the engine and wait
	 *        for any command to be issued.
	 *
	 */
	int engine_main();

	void fulfill_engine_termination_request();

	void fulfill_start_scan_request();

	void fulfill_start_fim_request();

private:
	/**
	 * @brief The engine will be running in a separate thread.
	 *
	 */
	std::thread *engine_thread;

	std::mutex mtx;

	std::condition_variable cv;

	bool engine_termination_requested;

	SAMScanner *scanner;

	bool start_scan_requested;

	void run();

	void clean_thread();
}; // class SAMEngine

class SAMScanner {
public:
	enum class State {
		IDLE,
		SCANNING,
		PAUSED,
		STOPPED,
		COMPLETE,
		ERROR
	};

	SAMScanner();
	~SAMScanner();

	void scan();

	void stop();

	void pause();

	void resume();

	SAMScanner::State get_state() const;

private:
	std::thread *scanner_thread;

	ScanAnalyzer *analyzer;

	SAMScanner::State current_state;

	/**
	 * @brief These two mutexes are used to protect the callback functions
	 *        from being called by multiple threads at the same time. This
	 *        is important because the callback functions modify the GUI.
	 *
	 */
	std::mutex add_new_file_callback_mtx;
	std::mutex update_new_file_callback_mtx;
	std::mutex update_engine_status_callback_mtx;

	void work([[maybe_unused]] size_t id, PEPathlsMonitor &monitor);

	void run();

	float generate_dummy_prediction();

	void switch_state(const SAMScanner::State &new_state);

	void clean_thread();
}; // class SAMScanner

/*
	When the engine start scanning a new file, it will call this callback
	with the new file's name to notify the GUI.
  */
typedef int (*AddNewFileCallback_t)();

/*
  When the engine finishes scanning a file, it will call this callback
  with the file's ID and the prediction to notify the GUI.
*/
typedef void (*UpdateNewFileCallback_t)(const int &, const int &, const std::string &, const float &);

typedef void (*ScannerStateChangeCallback_t)(const SAMScanner::State &);

typedef void (*UpdateEngineStatusCallback_t)(const std::string &, const SAMEngine::StatusMessageType &);

typedef int (*FIMNewEventCallback_t)();
typedef void (*FIMUpdateEventCallback_t)(const int &, const int &, const std::string &);

void hook_add_new_file_callback(const AddNewFileCallback_t &callback);
void hook_update_new_file_callback(const UpdateNewFileCallback_t &callback);
void hook_scanner_state_change_callback(const ScannerStateChangeCallback_t &callback);
void hook_update_engine_status_callback(const UpdateEngineStatusCallback_t &callback);

void hook_fim_new_event_callback(const FIMNewEventCallback_t &callback);
void hook_fim_update_event_callback(const FIMUpdateEventCallback_t &callback);
} // namespace sam_engine

#endif // SAM_STUB_ENGINE_HPP
