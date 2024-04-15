#ifndef SAM_CONSOLE_MAIN_HPP
#define SAM_CONSOLE_MAIN_HPP

// If the real engine is active, include the real engine.
#ifdef SAM_ENGINE_ACTIVE
#ifdef SAM_DUMMY_ENGINE_ACTIVE // If both engines are active, throw an error.
#error "Both real and dummy engines are active"
#else // If only the real engine is active, include the real engine.
#include "samengine.hpp"
#include "scanareasprocessor.hpp"
#endif // SAM_DUMMY_ENGINE_ACTIVE
#elif SAM_DUMMY_ENGINE_ACTIVE // If the dummy engine is active, include the dummy engine.
#include "samdummyengine.hpp"
#include "scanareasdummyprocessor.hpp"
typedef SAMDummyEngine SAMEngine;
typedef ScanAreasDummyProcessor ScanAreasProcessor;
#else // If no engine is active, throw an error.
#error "No engine found"
#endif // SAM_ENGINE_ACTIVE

#ifndef SAM_ORG_NAME
#error "No organization name defined"
#endif // SAM_ORG_NAME

#ifndef SAM_CONSOLE_PROJECT_NAME
#error "No project name defined"
#endif // SAM_CONSOLE_PROJECT_NAME

#ifndef SAM_CONSOLE_PROJECT_VERSION
#error "No project version defined"
#endif // SAM_CONSOLE_PROJECT_VERSION

#include "mainwindow.hpp"

extern SAMEngine *engine;

int main(int argc, char **argv);

void scan_fire_callback();

void scan_complete_callback();

int new_file_callback(const std::string& filename);

void status_callback(const int& row_index, const float& prediction);

#endif // SAM_CONSOLE_MAIN_HPP
