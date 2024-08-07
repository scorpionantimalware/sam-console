###################################################################################
#                                                                                 #
# CMakeLists.txt                                                                  #
#                                                                                 #
###################################################################################
#                                                                                 #
#    Scorpion Anti-malware Console is a free Open Source Qt-powered frontend      #
#    framework for SAM Engine.                                                    #
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

# TODO: We can use an older version of CMake.
cmake_minimum_required(VERSION 3.5)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type not set - defaulting to Debug")
  set(
    CMAKE_BUILD_TYPE "Debug"
    CACHE
      STRING
      "Choose the type of build from:  Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
endif()

set(SAM_ORG_NAME "Scorpion Anti-malware")

set(SAM_CONSOLE_PROJECT_NAME "Scorpion Anti-malware Console")

set(SAM_CONSOLE_PROJECT_VERSION "1.0.0")
set(SAM_CONSOLE_PROJECT_DESCRIPTION "Scorpion Anti-malware Console.")

set(SAM_CONSOLE_EXECUTABLE_NAME "sam-console")

project(${SAM_CONSOLE_EXECUTABLE_NAME} VERSION ${SAM_CONSOLE_PROJECT_VERSION} LANGUAGES CXX)

if (WIN32)
    string(APPEND CMAKE_CXX_FLAGS " /W4")
else()
    string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")
    string(APPEND CMAKE_C_FLAGS " -Wall -Wextra")

    # SAM console require a Windows build environment
    message(WARNING "Scorpion Anti-malware console requires a Windows build environment.")
endif()

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n"
  )
endif()

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Create code from a list of Qt designer ui files.
# set(CMAKE_AUTOUIC ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Create code from Qt rc files.
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable compiler-specific extensions for cross-platform compatibility.
set(CMAKE_CXX_EXTENSIONS OFF)

set(SAM_CONSOLE_ROOTDIR ${PROJECT_SOURCE_DIR})

if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /EHsc /wd26812")
    string(APPEND CMAKE_C_FLAGS " /EHsc /wd26812")
endif()

add_compile_definitions("SAM_CONSOLE_NO_EXCEPTIONS")

# Disable C++ exceptions.
if(MSVC)
    string(REGEX REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    add_definitions(-D_HAS_EXCEPTIONS=0)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables")
endif()

# Check https://stackoverflow.com/q/33062728/14629018 for more information.
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

set(SAM_CONSOLE_QT_VERSION "6")

file(GLOB SAM_CONSOLE_MAIN_ENTRY 
    ${CMAKE_CURRENT_SOURCE_DIR}/samconsolemain.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samconsolemain.cpp
)

file(GLOB SAM_CONSOLE_HPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samconsolesplash.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/homepage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/controlbar.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/scanbutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/stopbutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/pausebutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/resumebutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/scanareascontrollerbutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/scan-results-monitor/scanresultsmonitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/scan-areas-controller/scanareascontroller.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/scan-areas-controller/scanareascolumn.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/engine-status-monitor/enginestatusmonitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/page-switcher-bar/pageswitcherbar.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FIM-page/fimpage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FIM-page/events-monitor/eventsmonitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/about-page/aboutpage.hpp
)

file(GLOB SAM_CONSOLE_CPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samconsolesplash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/homepage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/controlbar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/scanbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/stopbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/pausebutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/resumebutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/control-bar/scanareascontrollerbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/scan-results-monitor/scanresultsmonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/scan-areas-controller/scanareascontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/scan-areas-controller/scanareascolumn.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/home-page/engine-status-monitor/enginestatusmonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/page-switcher-bar/pageswitcherbar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FIM-page/fimpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FIM-page/events-monitor/eventsmonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/about-page/aboutpage.cpp
)

# Safety check: Ensure that all the files exist.
foreach(file ${SAM_CONSOLE_CPP_FILES} ${SAM_CONSOLE_HPP_FILES} ${SAM_CONSOLE_MAIN_ENTRY})
    if(NOT EXISTS "${file}")
        message(FATAL_ERROR "File '${file}' does not exist!")
    endif()
endforeach()

set(${SAM_CONSOLE_EXECUTABLE_NAME}_INCLUDE_DIRECTORIES 
    "${CMAKE_CURRENT_SOURCE_DIR}/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/sam-stub-engine/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/page-switcher-bar/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/home-page/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/FIM-page/" 
    "${CMAKE_CURRENT_SOURCE_DIR}/about-page/"
)

if (NOT SAM_LINK_CONSOLE)
    # If the engine did not request to link the console, use the stub engine.

    message(STATUS "Building the console without an engine...")
    # TODO: Is this Windows specific?

    # Find Qt
    # TODO: Move this find package outside the if statement.
    find_package(Qt${SAM_CONSOLE_QT_VERSION} CONFIG REQUIRED COMPONENTS Widgets SvgWidgets)

    add_executable(${SAM_CONSOLE_EXECUTABLE_NAME} WIN32 
        ${SAM_CONSOLE_MAIN_ENTRY} 
        ${SAM_CONSOLE_CPP_FILES} 
    )

    target_compile_definitions(${SAM_CONSOLE_EXECUTABLE_NAME} PRIVATE 
        SAM_CONSOLE_NO_EXCEPTIONS 
        SAM_CONSOLE_ROOTDIR="${SAM_CONSOLE_ROOTDIR}" 
    )

    message(STATUS "Linking Qt${SAM_CONSOLE_QT_VERSION} to the console...")
    target_link_libraries(${SAM_CONSOLE_EXECUTABLE_NAME} PRIVATE 
        Qt${SAM_CONSOLE_QT_VERSION}::Widgets 
        Qt${SAM_CONSOLE_QT_VERSION}::SvgWidgets 
    )

    target_include_directories(${SAM_CONSOLE_EXECUTABLE_NAME} PRIVATE 
        ${${SAM_CONSOLE_EXECUTABLE_NAME}_INCLUDE_DIRECTORIES} 
    )

    # Link the stub engine.
    message(STATUS "Linking the stub engine to the console...")
    set(SAM_STUB_ENGINE_ROOTDIR "${SAM_CONSOLE_ROOTDIR}/sam-stub-engine")
    add_subdirectory(${SAM_STUB_ENGINE_ROOTDIR})

    target_link_libraries(${SAM_CONSOLE_EXECUTABLE_NAME} PRIVATE 
        ${SAM_STUB_ENGINE}
    )

    target_compile_definitions(${SAM_CONSOLE_EXECUTABLE_NAME} PRIVATE 
        SAM_ORG_NAME="${SAM_ORG_NAME}"
        SAM_CONSOLE_PROJECT_NAME="${SAM_CONSOLE_PROJECT_NAME}"
        SAM_CONSOLE_PROJECT_VERSION="${SAM_CONSOLE_PROJECT_VERSION}"
    )

    # Specify the directory containing the shared libraries.
    set(SAM_STUB_ENGINE_BUILD_ROOTDIR "${PROJECT_BINARY_DIR}/sam-stub-engine")
    
    # TODO: Why copy_if_different isn't working?
    # Copy the shared libraries to the executable directory.
    file(GLOB SAM_STUB_ENGINE_DLLS 
        "${SAM_STUB_ENGINE_BUILD_ROOTDIR}/Debug/${SAM_STUB_ENGINE}.dll"
    )

    # Safety check: Ensure that all the files exist.
    foreach(file ${SAM_STUB_ENGINE_DLLS})
        if(NOT EXISTS "${file}")
            message(FATAL_ERROR "File '${file}' does not exist!")
        endif()
    endforeach()

    foreach(SAM_STUB_ENGINE_DLL ${SAM_STUB_ENGINE_DLLS})
        add_custom_command(TARGET ${SAM_CONSOLE_EXECUTABLE_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy ${SAM_STUB_ENGINE_DLL} $<TARGET_FILE_DIR:${SAM_CONSOLE_EXECUTABLE_NAME}>
                        COMMENT "Copying ${SAM_STUB_ENGINE_DLL} to the executable directory."
        )
    endforeach()

else()
    # If the engine requested to link the console.

    set(SAM_CONSOLE_PROJECT_NAME ${SAM_CONSOLE_PROJECT_NAME} CACHE INTERNAL "Sam Console Project Name" FORCE)
    set(SAM_CONSOLE_PROJECT_VERSION ${SAM_CONSOLE_PROJECT_VERSION} CACHE INTERNAL "Sam Console Project Version" FORCE)

    set(SAM_CONSOLE_EXECUTABLE_NAME ${SAM_CONSOLE_EXECUTABLE_NAME} CACHE INTERNAL "Sam Console Executable Name" FORCE)

    set(SAM_CONSOLE_QT_VERSION ${SAM_CONSOLE_QT_VERSION} CACHE INTERNAL "Sam Console Qt Version" FORCE) 

    set(SAM_CONSOLE_ROOTDIR ${SAM_CONSOLE_ROOTDIR} CACHE INTERNAL "Sam Console Root Directory" FORCE) 

    # Cache the main entry files to be used in parent CMakeLists.txt file.
    set(SAM_CONSOLE_MAIN_ENTRY ${SAM_CONSOLE_MAIN_ENTRY} CACHE INTERNAL "Sam Console Main Entry" FORCE)
    set(SAM_CONSOLE_CPP_FILES ${SAM_CONSOLE_CPP_FILES} CACHE INTERNAL "Sam Console Source Files" FORCE)
    set(SAM_CONSOLE_HPP_FILES ${SAM_CONSOLE_HPP_FILES} CACHE INTERNAL "Sam Console Header Files" FORCE)

    set(${SAM_CONSOLE_EXECUTABLE_NAME}_INCLUDE_DIRECTORIES 
        ${${SAM_CONSOLE_EXECUTABLE_NAME}_INCLUDE_DIRECTORIES} CACHE INTERNAL "Sam Console Include Directories" FORCE
    )

endif()

#################################################
#
# Scorpion Anti-malware Console Tests
#
#################################################

if (SAM_CONSOLE_BUILD_TESTS)
    message(STATUS "Building Scorpion Anti-malware console tests...")
    set(SAM_CONSOLE_TESTS_ROOTDIR "${SAM_CONSOLE_ROOTDIR}/tests")
    add_subdirectory(${SAM_CONSOLE_TESTS_ROOTDIR})
endif()
