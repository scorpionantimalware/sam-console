#include "samdummyengine.hpp"

#include <iostream>
#include <random>

SAMDummyEngine::SAMDummyEngine() : engine_thread(nullptr), mtx(nullptr), scan_fire_callback(nullptr), scan_complete_callback(nullptr), new_file_callback(nullptr), status_callback(nullptr) {}

SAMDummyEngine::~SAMDummyEngine() {
    if (SAMDummyEngine::mtx) {
        delete SAMDummyEngine::mtx;
    }

    if (SAMDummyEngine::engine_thread) {
        if (SAMDummyEngine::engine_thread->joinable()) {
          SAMDummyEngine::engine_thread->join();
        }
        delete SAMDummyEngine::engine_thread;
    }
}

bool SAMDummyEngine::scan() {
  bool status {false};

  if (SAMDummyEngine::engine_thread) {
    status = SAMDummyEngine::engine_thread->joinable();
    if (status) {
      std::cout << "Error: Engine thread is already running" << std::endl;
      status = false;
      return status;
    }
    delete SAMDummyEngine::engine_thread;
  }

  SAMDummyEngine::engine_thread = new std::thread(&SAMDummyEngine::fire_scan, this);

  /*
    Detach the thread so that it can run independently of the main thread.

    Here in each scan, we will create a new thread so we do not need the current one.
  */
  SAMDummyEngine::engine_thread->detach();

  status = true;

  return status;
}

bool SAMDummyEngine::fire_scan() {
  if (SAMDummyEngine::scan_fire_callback) {
    SAMDummyEngine::scan_fire_callback();
  }

  bool status {false};

  int dummy_file_count {10};

  while (dummy_file_count--) {
    int new_file_id {-1};
    if (SAMDummyEngine::new_file_callback) {
      new_file_id = SAMDummyEngine::new_file_callback("dummy_file_" + std::to_string(dummy_file_count));
    }

    float dummy_prediction {SAMDummyEngine::generate_dummy_prediction()};

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (SAMDummyEngine::status_callback) {
      SAMDummyEngine::status_callback(new_file_id, dummy_prediction);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  if (SAMDummyEngine::scan_complete_callback) {
    SAMDummyEngine::scan_complete_callback();
  }

  status = true;

  return status;
}

float SAMDummyEngine::generate_dummy_prediction() {
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform real distribution between 0 and 1
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Generate a random number between 0 and 1
    return (float)dist(gen);
}

void SAMDummyEngine::hook_scan_fire_callback(ScanFireCallback_t callback) {
  SAMDummyEngine::scan_fire_callback = callback;
}

void SAMDummyEngine::hook_scan_complete_callback(ScanCompleteCallback_t callback) {
  SAMDummyEngine::scan_complete_callback = callback;
}

void SAMDummyEngine::hook_new_file_callback(NewFileCallback_t callback) {
  SAMDummyEngine::new_file_callback = callback;
}

void SAMDummyEngine::hook_status_callback(StatusCallback_t callback) {
  SAMDummyEngine::status_callback = callback;
}
