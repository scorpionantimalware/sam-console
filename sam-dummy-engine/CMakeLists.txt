# Caching the library name to be used in the parent scope.
set(SAM_DUMMY_ENGINE "sam_dummy_engine" CACHE STRING "Dummy SAM engine library name.")

file(GLOB SAM_DUMMY_ENGINE_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/samdummyengine.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/samdummyengine.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-dummy-processor/scanareasdummyprocessor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-dummy-processor/scanareasdummyprocessor.hpp
)

# Safety check: Ensure that all the files exist.
foreach(file ${SAM_DUMMY_ENGINE_SRC_FILES})
    if(NOT EXISTS "${file}")
        message(FATAL_ERROR "File '${file}' does not exist!")
    endif()
endforeach()

add_library(${SAM_DUMMY_ENGINE} SHARED  
    ${SAM_DUMMY_ENGINE_SRC_FILES} 
)

set_target_properties(${SAM_DUMMY_ENGINE} PROPERTIES VERSION ${SAM_CONSOLE_PROJECT_VERSION})

target_include_directories(${SAM_DUMMY_ENGINE} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-dummy-processor/"
)

# This is to build with the console with the dummy engine.
# There is another definition for the real engine.
target_compile_definitions(${SAM_DUMMY_ENGINE} PUBLIC 
    SAM_DUMMY_ENGINE_ACTIVE
)
