# TODO: We can use an older version of CMake.
cmake_minimum_required(VERSION 3.5)

option(LINK_CONSOLE "Builds Scorpion Anti-malware console and links the engine." OFF)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DSAM_CONSOLE_DEBUG)
endif()

set(SAM_CONSOLE_PROJECT_NAME "sam-console")

set(SAM_CONSOLE_PROJECT_VERSION "1.0.0")
set(SAM_CONSOLE_PROJECT_DESCRIPTION "Scorpion Anti-malware Console.")

project(${SAM_CONSOLE_PROJECT_NAME} VERSION ${SAM_CONSOLE_PROJECT_VERSION} LANGUAGES CXX)

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

# Check https://stackoverflow.com/q/33062728/14629018 for more information.
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

set(SAM_CONSOLE_QT_VERSION "6")

file(GLOB SAM_CONSOLE_SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/controlbar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/controlbar.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/scanbutton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/scanbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/stopbutton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/stopbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/pausebutton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/pausebutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/statusviewer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/statusviewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/summary.h
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/summary.cpp
)

# Find Qt
find_package(Qt${SAM_CONSOLE_QT_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets)

if (NOT LINK_CONSOLE)
    message(STATUS "Building the console without an engine...")
    # TODO: Is this Windows specific?
    add_executable(${SAM_CONSOLE_PROJECT_NAME} WIN32 
        ${CMAKE_CURRENT_SOURCE_DIR}/samconsolemain.cpp 
        ${SAM_CONSOLE_SRC_FILES} 
    )

    message(STATUS "Linking Qt${SAM_CONSOLE_QT_VERSION} to the console...")
    target_link_libraries(${SAM_CONSOLE_PROJECT_NAME} PRIVATE 
        Qt${SAM_CONSOLE_QT_VERSION}::Widgets 
    )

    target_include_directories(${SAM_CONSOLE_PROJECT_NAME} PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/control-bar/"
    )

else()
    message(STATUS "Building the console as library...")
    set(SAM_CONSOLE "sam_console" CACHE STRING "SAM console library name.")
    add_library(${SAM_CONSOLE} SHARED 
        ${SAM_CONSOLE_SRC_FILES} 
    )

    message(STATUS "Linking Qt${SAM_CONSOLE_QT_VERSION} to the console...")
    # Link with public because we build the executable in the engine's CMakeLists.txt file.
    target_link_libraries(${SAM_CONSOLE} PUBLIC 
        Qt${SAM_CONSOLE_QT_VERSION}::Widgets 
    )

    target_include_directories(${SAM_CONSOLE} PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/" 
        "${CMAKE_CURRENT_SOURCE_DIR}/control-bar/"
    )

endif()
