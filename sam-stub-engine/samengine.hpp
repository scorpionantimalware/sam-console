/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * samengine.hpp
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

#ifndef SAM_STUB_ENGINE_HPP
#define SAM_STUB_ENGINE_HPP

#include <thread>
#include <mutex>

namespace sam_engine {
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
  typedef int (*AddNewFileCallback_t)(const std::string&);

  /*
    When the engine finishes scanning a file, it will call this callback
    with the file's ID and the prediction to notify the GUI.
  */
  typedef void (*SetStatusForFileCallback_t)(const int&, const float&);

  class SAMEngineState {
    public:
      enum class State {
        IDLE,
        SCANNING,
        PAUSED,
        STOPPED,
        COMPLETE,
        ERROR
      };

      SAMEngineState();

      void set_state(const State& new_state);
      State get_state();

    private:
      State state;
  }; // class SAMEngineState

  typedef void (*EngineStateChangeCallback_t)(const SAMEngineState::State&);

  void hook_scan_fire_callback(const ScanFireCallback_t& callback);
  void hook_scan_complete_callback(const ScanCompleteCallback_t& callback);
  void hook_add_new_file_callback(const AddNewFileCallback_t& callback);
  void hook_set_status_for_file_callback(const SetStatusForFileCallback_t& callback);
  void hook_engine_state_change_callback(const EngineStateChangeCallback_t& callback);

  bool sam_engine_scan();
} // namespace sam_engine

#endif // SAM_STUB_ENGINE_HPP
