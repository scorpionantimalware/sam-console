###################################################################################
#                                                                                 #
# sam-stub-engine/CMakeLists.txt                                                  #
#                                                                                 #
###################################################################################
#                                                                                 #
#    Scorpion Anti-malware is a free Open Source AI-powered Anti-malware          #
#    framework for Researchers.                                                   #
#                                                                                 #
#    Copyright (c) 2024-present  (see AUTHORS.md).                                #
#                                                                                 #
#    This program is free software: you can redistribute it and/or modify         #
#    it under the terms of the GNU General Public License as published by         #
#    the Free Software Foundation, either version 3 of the License, or            #
#    (at your option) any later version.                                          #
#                                                                                 #
#    This program is distributed in the hope that it will be useful,              #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of               #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
#    GNU General Public License for more details.                                 #
#                                                                                 #
#    You should have received a copy of the GNU General Public License            #
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.       #
#                                                                                 #
###################################################################################


# Caching the library name to be used in the parent scope.
set(SAM_STUB_ENGINE "sam_stub_engine" CACHE STRING "Stub SAM engine library name.")

file(GLOB SAM_STUB_ENGINE_HPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/samengine.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/pepathlsmonitor.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-processor/scanareasprocessor.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/PE-pathls-generator/pepathlsgenerator.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/PE-pathls-generator/pepathlscollector.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-analyzer/scananalyzer.hpp 
)

file(GLOB SAM_STUB_ENGINE_CPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/samengine.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/pepathlsmonitor.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-areas-processor/scanareasprocessor.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/PE-pathls-generator/pepathlsgenerator.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/PE-pathls-generator/pepathlscollector.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/scan-analyzer/scananalyzer.cpp 
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
    "${CMAKE_CURRENT_SOURCE_DIR}/PE-pathls-generator/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/scan-analyzer/" 
)

# This is to build with the console with the engine.
# There is another definition for the real engine.
target_compile_definitions(${SAM_STUB_ENGINE} PUBLIC 
    SAM_STUB_ENGINE_ACTIVE 
)
