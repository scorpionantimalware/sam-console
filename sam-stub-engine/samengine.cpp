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

namespace sam_engine {
  ScanFireCallback_t scan_fire_callback {nullptr};
  ScanCompleteCallback_t scan_complete_callback {nullptr};
  AddNewFileCallback_t add_new_file_callback {nullptr};
  SetStatusForFileCallback_t set_status_for_file_callback {nullptr};
  EngineStateChangeCallback_t engine_state_change_callback {nullptr};
  UpdateBuiltinStatusTerminalCallback_t update_builtin_status_terminal_callback {nullptr};

  std::thread* engine_thread {nullptr};

  SAMEngineState* engine_state {nullptr};

  SAMEngineState::SAMEngineState() : state(SAMEngineState::State::IDLE) {
  } // constructor SAMEngineState

  void SAMEngineState::set_state(const State& new_state) {
    SAMEngineState::state = new_state;
    if (engine_state_change_callback) {
      engine_state_change_callback(SAMEngineState::state);
    }
  } // function set_state

  SAMEngineState::State SAMEngineState::get_state() {
    return SAMEngineState::state;
  } // function get_state

  /**
   * @brief Start the scan process
   * 
   * @note This function is the entry point for the scan process. This 
   *       function is Multi-threaded.
   * 
   * @note This function is a wrapper for the fire_scan() function to be
   *      called in a separate thread.
  */
  void fire_scan_thread_wrapper();

  bool fire_scan();

  float generate_dummy_prediction();

  bool sam_engine_scan() {
    bool status {false};

    if (!engine_state) {
      engine_state = new SAMEngineState();
    }

    engine_state->set_state(SAMEngineState::State::SCANNING);

    std::cout << "Info: Running the engine in a separate thread" << std::endl;
    if (update_builtin_status_terminal_callback) {
      update_builtin_status_terminal_callback("Running the engine in a separate thread", SAMEngineStatusMessage::INFO);
    }
    if (engine_thread) {
      status = engine_thread->joinable();
      if (status) {
        std::cout << "Error: Engine thread is already running" << std::endl;
        if (update_builtin_status_terminal_callback) {
          update_builtin_status_terminal_callback("Error: Engine thread is already running", SAMEngineStatusMessage::INFO);
        }
        engine_state->set_state(SAMEngineState::State::STOPPED);
        status = false;
        return status;
      }
      delete engine_thread;
    }

    engine_thread = new std::thread(&fire_scan_thread_wrapper);

    /*
      Detach the thread so that it can run independently of the main thread.

      Here in each scan, we will create a new thread so we do not need the current one.
    */
    engine_thread->detach();

    if (engine_thread) {
        if (engine_thread->joinable()) {
          engine_thread->join();
        }
        delete engine_thread;
    }

    status = true;

    return status;
  } // function sam_engine_scan

  void fire_scan_thread_wrapper() {
    bool status {false};

    status = fire_scan();
    if (!status) {
      std::cout << "Error: Something went wrong while scanning" << std::endl;
      if (update_builtin_status_terminal_callback) {
        update_builtin_status_terminal_callback("Error: Something went wrong while scanning", SAMEngineStatusMessage::INFO);
      }
    }
  } // function fire_scan_thread_wrapper

  bool fire_scan() {
    if (scan_fire_callback) {
      scan_fire_callback();
    }

    bool status {false};

    int dummy_file_count {10};

    while (dummy_file_count--) {
      int new_file_id {-1};
      if (add_new_file_callback) {
        new_file_id = add_new_file_callback("dummy_file_" + std::to_string(dummy_file_count));
      }

      float dummy_prediction {generate_dummy_prediction()};

      std::this_thread::sleep_for(std::chrono::seconds(1));

      if (set_status_for_file_callback) {
        set_status_for_file_callback(new_file_id, dummy_prediction);
        if (update_builtin_status_terminal_callback && dummy_prediction > 0.5) {
          update_builtin_status_terminal_callback("Suspicious file: dummy_file_" + std::to_string(dummy_file_count), SAMEngineStatusMessage::SUSPICIOUS_FILE);
        }
      }

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (scan_complete_callback) {
      scan_complete_callback();
    }

    engine_state->set_state(SAMEngineState::State::COMPLETE);

    status = true;

    return status;
  } // function fire_scan

  void sam_engine_stop() {
    // if (engine_thread) {
    //   if (engine_thread->joinable()) {
    //     engine_thread->join();
    //   }
    //   delete engine_thread;
    // }

    engine_state->set_state(SAMEngineState::State::STOPPED);

    // if (engine_state) {
    //   delete engine_state;
    // }
  } // function sam_engine_stop

  void sam_engine_pause() {
    
  } // function sam_engine_pause

  void sam_engine_resume() {
    
  } // function sam_engine_resume

  float generate_dummy_prediction() {
      // Create a random number generator engine
      std::random_device rd;
      std::mt19937 gen(rd());

      // Create a uniform real distribution between 0 and 1
      std::uniform_real_distribution<float> dist(0.0f, 1.0f);

      // Generate a random number between 0 and 1
      return dist(gen);
  } // function generate_dummy_prediction

  void hook_scan_fire_callback(const ScanFireCallback_t& callback) {
    scan_fire_callback = callback;
  } // function hook_scan_fire_callback

  void hook_scan_complete_callback(const ScanCompleteCallback_t& callback) {
    scan_complete_callback = callback;
  } // function hook_scan_complete_callback

  void hook_add_new_file_callback(const AddNewFileCallback_t& callback) {
    add_new_file_callback = callback;
  } // function hook_new_file_callback

  void hook_set_status_for_file_callback(const SetStatusForFileCallback_t& callback) {
    set_status_for_file_callback = callback;
  } // function hook_status_callback

  void hook_engine_state_change_callback(const EngineStateChangeCallback_t& callback) {
    engine_state_change_callback = callback;
  } // function hook_engine_state_change_callback

  void hook_update_builtin_status_terminal_callback(const UpdateBuiltinStatusTerminalCallback_t& callback) {
    update_builtin_status_terminal_callback = callback;
  } // function hook_update_builtin_status_terminal_callback
} // namespace sam_engine
