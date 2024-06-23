/**********************************************************************************/
/*                                                                                */
/* samengine.cpp (stub)                                                           */
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


#include "samengine.hpp"

#include <iostream>
#include <random>
#include <fstream>

#include "pepathlsgenerator.hpp"
#include "scanareasprocessor.hpp"

#define SAM_ENGINE_MAX_JOBS 10

namespace sam_engine {
  AddNewFileCallback_t add_new_file_callback {nullptr};
  UpdateNewFileCallback_t update_new_file_callback {nullptr};
  ScannerStateChangeCallback_t scanner_state_change_callback {nullptr};
  UpdateEngineStatusCallback_t update_engine_status_callback {nullptr};

  FIMNewEventCallback_t fim_new_event_callback {nullptr};

  SAMEngine::SAMEngine() : engine_thread(nullptr), 
                            engine_termination_requested(false), 
                            scanner(nullptr), 
                            start_scan_requested(false) {} // constructor SAMEngine

  SAMEngine::~SAMEngine() {
    if (SAMEngine::scanner) {
      delete SAMEngine::scanner;
      SAMEngine::scanner = nullptr;
    }

    SAMEngine::clean_thread();
  } // destructor SAMEngine

  int SAMEngine::engine_main() {
    if (SAMEngine::engine_thread) {
      std::cout << "Error: Engine thread already exists" << std::endl;
      return -1;
    }

    SAMEngine::engine_thread = new std::thread(&SAMEngine::run, this); 

    /*
      Detach the thread so that it can run independently of the main thread.

      Here in each scan, we will create a new thread so we do not need the current one.
    */
    // SAMEngine::engine_thread->detach();

    return 0;
  } // function engine_main

  void SAMEngine::fulfill_engine_termination_request() {
    {
      std::lock_guard<std::mutex> lock(SAMEngine::mtx);
      SAMEngine::engine_termination_requested = true;
    }
    SAMEngine::cv.notify_one(); // Notify the engine thread.
  } // function fulfill_engine_termination_request

  void SAMEngine::fulfill_start_scan_request() {
    {
      std::lock_guard<std::mutex> lock(SAMEngine::mtx);
      SAMEngine::start_scan_requested = true;
    }
    SAMEngine::cv.notify_one(); // Notify the engine thread.
  } // function fulfill_start_scan_request

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
                SAMEngine::start_scan_requested;
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

        // Only scan if the scanner is idle.
        if (SAMEngine::scanner->get_state() == SAMScanner::State::IDLE) {
          SAMEngine::scanner->scan();
        }
      }
    } // while (true)

    std::cout << "Info: Engine is stopped" << std::endl;
  } // function run

  void SAMEngine::clean_thread() {
    if (SAMEngine::engine_thread) {
      // Since the engine thread is detached, we can't join it (Detaching disabled)
      if (SAMEngine::engine_thread->joinable()) {
        SAMEngine::engine_thread->join();
      }
      delete SAMEngine::engine_thread;
      SAMEngine::engine_thread = nullptr;
    }
  } // function clean_thread

  SAMScanner::SAMScanner() : scanner_thread(nullptr),
                              analyzer(nullptr),
                              current_state(SAMScanner::State::IDLE) {
    SAMScanner::analyzer = new ScanAnalyzer();
  } // constructor SAMScanner

  SAMScanner::~SAMScanner() {
    if (SAMScanner::analyzer) {
      delete SAMScanner::analyzer;
      SAMScanner::analyzer = nullptr;
    }

    SAMScanner::clean_thread();
  } // destructor SAMScanner

  void SAMScanner::scan() {
    // Set the current state to SCANNING.
    SAMScanner::switch_state(SAMScanner::State::SCANNING);

    if (update_engine_status_callback) {
      std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
      update_engine_status_callback("Scanning started",
                                    SAMEngine::StatusMessageType::INFO);
    }

    // Clean the thread before starting a new one.
    SAMScanner::clean_thread();

    SAMScanner::scanner_thread = new std::thread(&SAMScanner::run, this);

    /*
      Detach the thread so that it can run independently of the engine thread.

      Here in each scan, we will create a new thread so we do not need the current one.
    */
    // SAMScanner::scanner_thread->detach();
  }

  void SAMScanner::run() {
    bool status {false};

    ScanAreasProcessor scan_areas_processor;
    std::vector<std::string> scan_areas;
    status = scan_areas_processor.load_or_init(scan_areas);
    if (!status) {
      std::cout << "Error: Failed to load or initialize scan areas"
                << std::endl;

      if (update_engine_status_callback) {
        std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
        update_engine_status_callback("Failed to load or initialize scan areas",
                                      SAMEngine::StatusMessageType::ERROR);
      }
      
      // Set the current state to IDLE.
      SAMScanner::switch_state(SAMScanner::State::IDLE);
      return;
    }

    if (scan_areas.empty()) {
      std::cout << "Info: No scan areas found" << std::endl;

      if (update_engine_status_callback) {
        std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
        update_engine_status_callback("No scan areas found",
                                      SAMEngine::StatusMessageType::INFO);
      }
      
      // Set the current state to IDLE.
      SAMScanner::switch_state(SAMScanner::State::IDLE);
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

        if (update_engine_status_callback) {
          std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
          update_engine_status_callback("Failed to generate .pathl file",
                                        SAMEngine::StatusMessageType::ERROR);
        }
        
        // Set the current state to IDLE.
        SAMScanner::switch_state(SAMScanner::State::IDLE);
        return;
      }

      // Next scan area.
      i++;
    }

    // Now the generator is released.
    std::cout << "Info: .pathl file generated" << std::endl;

    if (update_engine_status_callback) {
      std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
      update_engine_status_callback(".pathl file generated",
                                    SAMEngine::StatusMessageType::INFO);
    }
    
    // Collect the paths from the .pathl file.
    // TODO: Don't open the full file at once. Load a batch and close the file.
    std::ifstream pe_pathls_file(PE_PATHLS_FILENAME);
    if (!pe_pathls_file.is_open()) {
      std::cout << "Error: Failed to open .pathl file" << std::endl;

      if (update_engine_status_callback) {
        std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
        update_engine_status_callback("Failed to open .pathl file",
                                      SAMEngine::StatusMessageType::ERROR);
      }
      
      // Set the current state to IDLE.
      SAMScanner::switch_state(SAMScanner::State::IDLE);
      return;
    }

    PEPathlsMonitor monitor;
    
    // Create our scanning workers
    std::vector<std::thread> scanning_workers;
    for (size_t j {0}; j < SAM_ENGINE_MAX_JOBS; j++) {
      scanning_workers.emplace_back(&SAMScanner::work, this, j,
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

    // Set the current state to IDLE.
    SAMScanner::switch_state(SAMScanner::State::IDLE);

    if (update_engine_status_callback) {
      std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
      update_engine_status_callback("Scanning completed",
                                    SAMEngine::StatusMessageType::INFO);
    }
  }

  void SAMScanner::stop() {

  }

  void SAMScanner::pause() {

  }

  void SAMScanner::resume() {

  }

  void SAMScanner::clean_thread() {
    if (SAMScanner::scanner_thread) {
      // Since the scanner thread is detached, we can't join it (Detaching disabled)
      if (SAMScanner::scanner_thread->joinable()) {
        SAMScanner::scanner_thread->join();
      }
      delete SAMScanner::scanner_thread;
      SAMScanner::scanner_thread = nullptr;
    }
  }

  SAMScanner::State SAMScanner::get_state() const {
    return SAMScanner::current_state;
  }

  void SAMScanner::switch_state(const SAMScanner::State& new_state) {
    SAMScanner::current_state = new_state;
    // TODO: Fix this.
    // if (scanner_state_change_callback) {
    //   scanner_state_change_callback(SAMScanner::current_state);
    // }
  }

  void SAMScanner::work([[maybe_unused]] size_t id, PEPathlsMonitor &monitor) {
    std::string pathl_buffer;
    while (monitor.get_pe_pathl(pathl_buffer)) {
      std::cout << "Info: Scanning " << pathl_buffer << std::endl;

      /*
        This ID is used to get the file entry from the table inside the GUI.
      */
      int new_file_id {-1};
      if (add_new_file_callback) {
        // The status callback modifies the GUI so we want to make sure that
        // only one thread does it at a time.
        std::lock_guard<std::mutex> add_new_file_callback_lock(SAMScanner::add_new_file_callback_mtx);
        new_file_id = add_new_file_callback();
      }

      if (new_file_id == -1) {
        std::cout << "Error: Failed to get the new file ID" << std::endl;

        if (update_engine_status_callback) {
            std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
            update_engine_status_callback("Failed to get the new file ID",
                SAMEngine::StatusMessageType::ERROR);
        }

        continue;
      }

      if (update_new_file_callback) {
        // The status callback modifies the GUI so we want to make sure that 
        // only one thread does it at a time.
        // TODO: Do we need to lock the mutex here?
        // std::lock_guard<std::mutex> set_file_status_callback_lock(SAMScanner::set_file_status_callback_mtx);
        update_new_file_callback(new_file_id, 0, pathl_buffer, -1.0f); // 0 is the column index for the filename
        update_new_file_callback(new_file_id, 1, "Scanning", -1.0f); // 1 is the column index for the status
      }

      // Classify the PE file.
      float annoutput {generate_dummy_prediction()};

      // Classify the PE file for CNN.
      float cnnoutput {generate_dummy_prediction()};

      // Simulate the delay of the classification process.
      std::this_thread::sleep_for(std::chrono::seconds(1));

      /*
        This is the static voting mechanism.
      */
      float prediction {(annoutput + cnnoutput) * 0.5f};

      std::string prediction_status {"Failed"};

      if (prediction == -1.0f || prediction < 0.0f || prediction > 1.0f) {
        if (update_new_file_callback) {
          // The status callback modifies the GUI so we want to make sure that 
          // only one thread does it at a time.
          // TODO: Do we need to lock the mutex here?
          // std::lock_guard<std::mutex> set_file_status_callback_lock(SAMScanner::set_file_status_callback_mtx);
          update_new_file_callback(new_file_id, 1, prediction_status, -1.0f); // 1 is the column index for the status
        }
        continue;
      }

      if (prediction > 0.5f) {
        prediction_status = "Malware";

        if (update_engine_status_callback) {
          std::lock_guard<std::mutex> update_engine_status_callback_lock(SAMScanner::update_engine_status_callback_mtx);
          update_engine_status_callback(pathl_buffer + " is malware",
                                        SAMEngine::StatusMessageType::WARNING);
        }

      } else {
        prediction_status = "Benign";
      }

      if (update_new_file_callback) {
        // The status callback modifies the GUI so we want to make sure that 
        // only one thread does it at a time.
        // TODO: Do we need to lock the mutex here?
        // std::lock_guard<std::mutex> set_file_status_callback_lock(SAMScanner::set_file_status_callback_mtx);
        update_new_file_callback(new_file_id, 1, prediction_status, prediction); // 1 is the column index for the status
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

  void hook_update_new_file_callback(const UpdateNewFileCallback_t& callback) {
    update_new_file_callback = callback;
  } // function hook_update_new_file_callback

  void hook_scanner_state_change_callback(const ScannerStateChangeCallback_t& callback) {
    scanner_state_change_callback = callback;
  } // function hook_scanner_state_change_callback

  void hook_update_engine_status_callback(const UpdateEngineStatusCallback_t& callback) {
    update_engine_status_callback = callback;
  } // function hook_update_engine_status_callback


  void hook_fim_new_event_callback(const FIMNewEventCallback_t& callback) {
    fim_new_event_callback = callback;
  } // function hook_fim_new_event_callback
} // namespace sam_engine
