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
        void engine_main();

        void fulfill_engine_termination_request();

        void fulfill_start_scan_request();

      private:
      /**
       * @brief The engine will be running in a separate thread.
       * 
       */
        std::thread* engine_thread;

        std::mutex mtx;

        std::condition_variable cv;

        bool engine_termination_requested;

        SAMScanner* scanner;

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

        void switch_state(const SAMScanner::State& new_state);

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
    typedef void (*UpdateNewFileCallback_t)(const int&, const int&, const std::string&, const float&);

    typedef void (*ScannerStateChangeCallback_t)(const SAMScanner::State&);

    typedef void (*UpdateEngineStatusCallback_t)(const std::string&, const SAMEngine::StatusMessageType&);

    void hook_add_new_file_callback(const AddNewFileCallback_t& callback);
    void hook_update_new_file_callback(const UpdateNewFileCallback_t& callback);
    void hook_scanner_state_change_callback(const ScannerStateChangeCallback_t& callback);
    void hook_update_engine_status_callback(const UpdateEngineStatusCallback_t& callback);
} // namespace sam_engine

#endif // SAM_STUB_ENGINE_HPP
