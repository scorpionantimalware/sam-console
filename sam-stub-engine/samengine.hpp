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

#include <condition_variable>

#include <atomic>

#include "pepathlsmonitor.hpp"

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
      void engine_main();

      void fulfill_engine_termination_request();

      void fulfill_start_scan_request();
      void fulfill_stop_scan_request();
      void fulfill_pause_scan_request();
      void fulfill_resume_scan_request();

    private:
    /**
     * @brief The engine will be running in a separate thread.
     * 
     */
      std::thread* engine_thread;

      std::mutex mtx;

      std::condition_variable cv;

      std::atomic<bool> engine_termination_requested;

      SAMScanner* scanner;

      bool start_scan_requested;
      bool stop_scan_requested;
      bool pause_scan_requested;
      bool resume_scan_requested;

      void run();

      void clean();

      void terminate_engine();

  }; // class SAMEngine

  class SAMScanner {
    public:
      enum class State {
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

    private:
      std::thread *scanner_thread;

      std::mutex mtx;
      std::condition_variable cv;
      std::atomic<bool> termination_requested;
      std::atomic<bool> pause_requested;

      /**
       * @brief These two mutexes are used to protect the callback functions
       *        from being called by multiple threads at the same time. This 
       *        is important because the callback functions modify the GUI.
       * 
       */
      std::mutex add_new_file_callback_mtx;
      std::mutex set_result_for_file_callback_mtx;

      void work(PEPathlsMonitor &monitor);

      void run();

      float generate_dummy_prediction();
  }; // class SAMScanner

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

    typedef void (*ScannerStateChangeCallback_t)(const SAMScanner::State&);

    typedef void (*UpdateBuiltinStatusTerminalCallback_t)(const std::string&, const SAMEngine::StatusMessageType&);

    void hook_add_new_file_callback(const AddNewFileCallback_t& callback);
    void hook_set_result_for_file_callback(const SetResultForFileCallback_t& callback);
    void hook_scanner_state_change_callback(const ScannerStateChangeCallback_t& callback);
    void hook_update_builtin_status_terminal_callback(const UpdateBuiltinStatusTerminalCallback_t& callback);
} // namespace sam_engine

#endif // SAM_STUB_ENGINE_HPP
