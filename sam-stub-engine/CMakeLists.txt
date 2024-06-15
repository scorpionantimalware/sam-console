# Caching the library name to be used in the parent scope.
set(SAM_STUB_ENGINE "sam_stub_engine" CACHE STRING "Stub SAM engine library name.")

file(GLOB SAM_STUB_ENGINE_HPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/samengine.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-processor/scanareasprocessor.hpp 
)

file(GLOB SAM_STUB_ENGINE_CPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/samengine.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-processor/scanareasprocessor.cpp 
)

# Safety check: Ensure that all the files exist.
foreach(file ${SAM_STUB_ENGINE_CPP_FILES} ${SAM_STUB_ENGINE_HPP_FILES})
    if(NOT EXISTS "${file}")
        message(FATAL_ERROR "File '${file}' does not exist!")
    endif()
endforeach()

add_library(${SAM_STUB_ENGINE} SHARED  
    ${SAM_STUB_ENGINE_CPP_FILES} 
)

set_target_properties(${SAM_STUB_ENGINE} PROPERTIES VERSION ${SAM_CONSOLE_PROJECT_VERSION})

target_include_directories(${SAM_STUB_ENGINE} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-processor/"
)

# This is to build with the console with the  engine.
# There is another definition for the real engine.
target_compile_definitions(${SAM_STUB_ENGINE} PUBLIC 
    SAM_STUB_ENGINE_ACTIVE
)
