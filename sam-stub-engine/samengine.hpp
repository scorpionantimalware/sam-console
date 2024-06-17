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
      State get_state() const;

    private:
      State state;
  }; // class SAMEngineState

  enum class SAMEngineStatusMessage {
    INFO,
    CLEAN_FILE,
    SUSPICIOUS_FILE,
    ERROR
  };

  /*
    When the engine start scanning a new file, it will call this callback
    with the new file's name to notify the GUI.
  */
  typedef int (*AddNewFileCallback_t)(const std::string&);

  /*
    When the engine finishes scanning a file, it will call this callback
    with the file's ID and the prediction to notify the GUI.
  */
  typedef void (*SetResultForFileCallback_t)(const int&, const float&);

  typedef void (*EngineStateChangeCallback_t)(const SAMEngineState&);

  typedef void (*UpdateBuiltinStatusTerminalCallback_t)(const std::string&, const SAMEngineStatusMessage&);

  void hook_add_new_file_callback(const AddNewFileCallback_t& callback);
  void hook_set_result_for_file_callback(const SetResultForFileCallback_t& callback);
  void hook_engine_state_change_callback(const EngineStateChangeCallback_t& callback);
  void hook_update_builtin_status_terminal_callback(const UpdateBuiltinStatusTerminalCallback_t& callback);

  bool sam_engine_scan();

  void sam_engine_stop();

  void sam_engine_pause();

  void sam_engine_resume();
} // namespace sam_engine

#endif // SAM_STUB_ENGINE_HPP
