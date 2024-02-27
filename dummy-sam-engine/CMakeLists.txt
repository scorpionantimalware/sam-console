# Caching the library name to be used in the parent scope.
set(DUMMY_SAM_ENGINE "dummy_sam_engine" CACHE STRING "Dummy SAM engine library name.")

file(GLOB DUMMY_SAM_ENGINE_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy-sam-engine.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy-sam-engine.cpp 
)

add_library(${DUMMY_SAM_ENGINE} SHARED  
    ${DUMMY_SAM_ENGINE_SRC_FILES} 
)

set_target_properties(${DUMMY_SAM_ENGINE} PROPERTIES VERSION ${SAM_CONSOLE_PROJECT_VERSION})

target_include_directories(${DUMMY_SAM_ENGINE} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/" 
)
