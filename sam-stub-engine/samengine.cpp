/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * samengine.cpp
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

#include "samengine.hpp"

#include <iostream>
#include <random>
#include <fstream>

#include "pepathlsgenerator.hpp"
#include "scanareasprocessor.hpp"

#define SAM_ENGINE_MAX_JOBS 4

namespace sam_engine {
  AddNewFileCallback_t add_new_file_callback {nullptr};
  SetResultForFileCallback_t set_result_for_file_callback {nullptr};
  ScannerStateChangeCallback_t scanner_state_change_callback {nullptr};
  UpdateBuiltinStatusTerminalCallback_t update_builtin_status_terminal_callback {nullptr};

  SAMEngine::SAMEngine() : engine_thread(nullptr), 
                            engine_termination_requested(false), 
                            scanner(nullptr), 
                            start_scan_requested(false), 
                            stop_scan_requested(false), 
                            pause_scan_requested(false), 
                            resume_scan_requested(false) {} // constructor SAMEngine

  SAMEngine::~SAMEngine() {
    SAMEngine::clean();
  } // destructor SAMEngine

  void SAMEngine::engine_main() {
    SAMEngine::engine_thread = new std::thread(&SAMEngine::run, this); 

    /*
      Detach the thread so that it can run independently of the main thread.

      Here in each scan, we will create a new thread so we do not need the current one.
    */
    SAMEngine::engine_thread->detach();
  } // function engine_main

  void SAMEngine::fulfill_engine_termination_request() {
    std::lock_guard<std::mutex> lock(SAMEngine::mtx);
    SAMEngine::engine_termination_requested = true;
    SAMEngine::cv.notify_all();
  } // function fulfill_engine_termination_request

  void SAMEngine::fulfill_start_scan_request() {
    std::lock_guard<std::mutex> lock(SAMEngine::mtx);
    SAMEngine::start_scan_requested = true;
    SAMEngine::cv.notify_all();
  } // function fulfill_start_scan_request

  void SAMEngine::fulfill_stop_scan_request() {
    std::lock_guard<std::mutex> lock(SAMEngine::mtx);
    SAMEngine::stop_scan_requested = true;
    SAMEngine::cv.notify_all();
  } // function fulfill_stop_scan_request

  void SAMEngine::fulfill_pause_scan_request() {
    std::lock_guard<std::mutex> lock(SAMEngine::mtx);
    SAMEngine::pause_scan_requested = true;
    SAMEngine::cv.notify_all();
  } // function fulfill_pause_scan_request

  void SAMEngine::fulfill_resume_scan_request() {
    std::lock_guard<std::mutex> lock(SAMEngine::mtx);
    SAMEngine::resume_scan_requested = true;
    SAMEngine::cv.notify_all();
  } // function fulfill_resume_scan_request

  void SAMEngine::run() {

    std::cout << "Info: Engine made it" << std::endl;

    ////////////////////////////////////////////////////
    // 
    // Main engine loop
    //
    ////////////////////////////////////////////////////
    while (true) {
      std::unique_lock<std::mutex> lock(SAMEngine::mtx);

      cv.wait(lock, [&] { 
        return SAMEngine::engine_termination_requested || 
                SAMEngine::start_scan_requested ||
                SAMEngine::stop_scan_requested ||
                SAMEngine::pause_scan_requested ||
                SAMEngine::resume_scan_requested;
      });

      if (SAMEngine::engine_termination_requested) {
        break;
      }

      std::cout << "Info: Engine is running" << std::endl;

      if (SAMEngine::start_scan_requested) {
        SAMEngine::start_scan_requested = false;

        if (!SAMEngine::scanner) {
          SAMEngine::scanner = new SAMScanner();
        }

        SAMEngine::scanner->scan();
      }

      if (SAMEngine::stop_scan_requested) {
        SAMEngine::stop_scan_requested = false;

        if (SAMEngine::scanner) {
          SAMEngine::scanner->stop();
        }
      }

      if (SAMEngine::pause_scan_requested) {
        SAMEngine::pause_scan_requested = false;

        if (SAMEngine::scanner) {
          SAMEngine::scanner->pause();
        }
      }

      if (SAMEngine::resume_scan_requested) {
        SAMEngine::resume_scan_requested = false;

        if (SAMEngine::scanner) {
          SAMEngine::scanner->resume();
        }
      }
    } // while (true)

    std::cout << "Info: Engine is stopped" << std::endl;
  } // function run

  void SAMEngine::clean() {
    if (SAMEngine::scanner) {
      delete SAMEngine::scanner;
    }

    if (SAMEngine::engine_thread) {
      if (SAMEngine::engine_thread->joinable()) {
        SAMEngine::engine_thread->join();
      }
      delete SAMEngine::engine_thread;
    }
  } // function clean

  SAMScanner::SAMScanner() : scanner_thread(nullptr), termination_requested(false), 
                              pause_requested(false) {
    
  } // constructor SAMScanner

  SAMScanner::~SAMScanner() {
    if (SAMScanner::scanner_thread) {
      if (SAMScanner::scanner_thread->joinable()) {
        SAMScanner::scanner_thread->join();
      }
      delete SAMScanner::scanner_thread;
    }
  } // destructor SAMScanner

  void SAMScanner::scan() {
    SAMScanner::termination_requested = false;
    SAMScanner::pause_requested = false;

    SAMScanner::scanner_thread = new std::thread(&SAMScanner::run, this);

    /*
      Detach the thread so that it can run independently of the engine thread.

      Here in each scan, we will create a new thread so we do not need the current one.
    */
    SAMScanner::scanner_thread->detach();
  }

  void SAMScanner::run() {
    bool status {false};

    ScanAreasProcessor scan_areas_processor;
    std::vector<std::string> scan_areas;
    status = scan_areas_processor.load_or_init(scan_areas);
    if (!status) {
      std::cout << "Error: Failed to load or initialize scan areas"
                << std::endl;
      if (update_builtin_status_terminal_callback) {
        update_builtin_status_terminal_callback("Error: Failed to load or initialize scan areas", SAMEngine::StatusMessageType::ERROR);
      }
      
      // engine_state->set_state(SAMEngineState::State::STOPPED);
      return;
    }

    if (scan_areas.empty()) {
      std::cout << "Info: No scan areas found" << std::endl;
      if (update_builtin_status_terminal_callback) {
        update_builtin_status_terminal_callback("Info: No scan areas found", SAMEngine::StatusMessageType::INFO);
      }
      
      // engine_state->set_state(SAMEngineState::State::STOPPED);
      return;
    }

    PEPathlsGenerator generator;

    // Generate the .pathl file.
    size_t i {0};
    while (i < scan_areas.size()) {

      // Generate paths for each scan area.
      status = generator.generate(scan_areas.at(i));
      if (!status) {
        std::cout << "Error: Failed to generate .pathl file" << std::endl;
        if (update_builtin_status_terminal_callback) {
          update_builtin_status_terminal_callback("Error: Failed to generate .pathl file", SAMEngine::StatusMessageType::ERROR);
        }
        // engine_state->set_state(SAMEngineState::State::STOPPED);
        return;
      }

      // Next scan area.
      i++;
    }

    // Now the generator is released.
    std::cout << "Info: .pathl file generated" << std::endl;
    
    // Collect the paths from the .pathl file.
    // TODO: Don't open the full file at once. Load a batch and close the file.
    std::ifstream pe_pathls_file(PE_PATHLS_FILENAME);
    if (!pe_pathls_file.is_open()) {
      std::cout << "Error: Failed to open .pathl file" << std::endl;
      if (update_builtin_status_terminal_callback) {
        update_builtin_status_terminal_callback("Error: Failed to open .pathl file", SAMEngine::StatusMessageType::ERROR);
      }
      
      // engine_state->set_state(SAMEngineState::State::STOPPED);
      return;
    }

    PEPathlsMonitor monitor;
    
    // Create our scanning workers
    std::vector<std::thread> scanning_workers;
    for (size_t j {0}; j < SAM_ENGINE_MAX_JOBS; j++) {
      scanning_workers.emplace_back(&SAMScanner::work, this,
        std::ref(monitor));
    }

    std::string pe_pathl_buffer;
    while (std::getline(pe_pathls_file, pe_pathl_buffer)) {
      monitor.add_pe_pathl(pe_pathl_buffer);
    }

    pe_pathls_file.close();

    // Notify workers that no more files will be added
    monitor.set_done();

    for (auto& worker : scanning_workers) {
      if (worker.joinable()) {
        worker.join();
      }
    }
  }

  void SAMScanner::stop() {
    {
      std::lock_guard<std::mutex> lock(SAMScanner::mtx);
      SAMScanner::termination_requested = true;
      SAMScanner::pause_requested = false;
    }
    SAMScanner::cv.notify_all();
  }

  void SAMScanner::pause() {
    std::lock_guard<std::mutex> lock(SAMScanner::mtx);
    SAMScanner::pause_requested = true;
  }

  void SAMScanner::resume() {
    {
      std::lock_guard<std::mutex> lock(SAMScanner::mtx);
      SAMScanner::pause_requested = false;
    }
    SAMScanner::cv.notify_all();
  }

  void SAMScanner::work(PEPathlsMonitor &monitor) {
    std::string pathl_buffer;
    while (!SAMScanner::termination_requested && monitor.get_pe_pathl(pathl_buffer)) {
      std::unique_lock<std::mutex> lock(SAMScanner::mtx);

      /**
       * @brief If the scanner is paused or stopped, wait for the condition.
       *        If the scanner is stopped, break the loop.
       * 
       */
      SAMScanner::cv.wait(lock, [&] { 
        return !SAMScanner::pause_requested || 
                SAMScanner::termination_requested; 
      });

      if (SAMScanner::termination_requested) {
        break;
      }
      
      std::cout << "Info: Scanning " << pathl_buffer << std::endl;

      /*
        This ID is used to get the file entry from the table inside the GUI.
      */
      int new_file_id {-1};
      if (add_new_file_callback) {
        {
          // The status callback modifies the GUI so we want to make sure that
          // only one thread does it at a time.
          std::lock_guard<std::mutex> add_new_file_callback_lock(SAMScanner::add_new_file_callback_mtx);
          new_file_id = add_new_file_callback(pathl_buffer);
        }
        if (new_file_id == -1) {
          std::cout << "Error: Failed to get the new file ID" << std::endl;
          if (update_builtin_status_terminal_callback) {
            update_builtin_status_terminal_callback("Error: Failed to get the new file ID", SAMEngine::StatusMessageType::ERROR);
          }
          continue;
        }
      }

      // Classify the PE file.
      float annoutput {generate_dummy_prediction()};

      // Classify the PE file for CNN.
      float cnnoutput {generate_dummy_prediction()};

      /*
        This is the static voting mechanism.
      */
      float prediction {(annoutput + cnnoutput) * 0.5f};

      if (set_result_for_file_callback) {
        // The status callback modifies the GUI so we want to make sure that 
        // only one thread does it at a time.
        // TODO: Do we need to lock the mutex here?
        // std::lock_guard<std::mutex> set_result_for_file_callback_lock(SAMScanner::set_result_for_file_callback_mtx);
        set_result_for_file_callback(new_file_id, prediction);
        if (update_builtin_status_terminal_callback && prediction > 0.5f) {
          update_builtin_status_terminal_callback("Malware detected in " + pathl_buffer, SAMEngine::StatusMessageType::INFO);
        }
      }
    } // while (!SAMScanner::termination_requested && monitor.get_pe_pathl(pathl_buffer))
  } // function work

  float SAMScanner::generate_dummy_prediction() {
      // Create a random number generator engine
      std::random_device rd;
      std::mt19937 gen(rd());

      // Create a uniform real distribution between 0 and 1
      std::uniform_real_distribution<float> dist(0.0f, 1.0f);

      // Generate a random number between 0 and 1
      return dist(gen);
  } // function generate_dummy_prediction

  void hook_add_new_file_callback(const AddNewFileCallback_t& callback) {
    add_new_file_callback = callback;
  } // function hook_new_file_callback

  void hook_set_result_for_file_callback(const SetResultForFileCallback_t& callback) {
    set_result_for_file_callback = callback;
  } // function hook_status_callback

  void hook_scanner_state_change_callback(const ScannerStateChangeCallback_t& callback) {
    scanner_state_change_callback = callback;
  } // function hook_scanner_state_change_callback

  void hook_update_builtin_status_terminal_callback(const UpdateBuiltinStatusTerminalCallback_t& callback) {
    update_builtin_status_terminal_callback = callback;
  } // function hook_update_builtin_status_terminal_callback
} // namespace sam_engine
