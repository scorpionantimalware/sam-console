#ifndef SAM_DUMMY_ENGINE_H
#define SAM_DUMMY_ENGINE_H

#include <thread>
#include <mutex>

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
typedef int (*NewFileCallback_t)(const std::string&);

/*
  When the engine finishes scanning a file, it will call this callback
  with the file's ID and the prediction to notify the GUI.
*/
typedef void (*StatusCallback_t)(const int&, const float&);

class SAMDummyEngine {
 public:
  SAMDummyEngine();
  ~SAMDummyEngine();

  bool scan();

  void hook_scan_fire_callback(ScanFireCallback_t callback);
  void hook_scan_complete_callback(ScanCompleteCallback_t callback);
  void hook_new_file_callback(NewFileCallback_t callback);
  void hook_status_callback(StatusCallback_t callback);

  private:
    std::thread* engine_thread;
    std::mutex* mtx;

    bool fire_scan();

    ScanFireCallback_t scan_fire_callback;
    ScanCompleteCallback_t scan_complete_callback;
    NewFileCallback_t new_file_callback;
    StatusCallback_t status_callback;

    float generate_dummy_prediction();
}; // class SAMDummyEngine

#endif // SAM_DUMMY_ENGINE_H
