cmake_minimum_required(VERSION 3.5)

option(LINK_CONSOLE "Builds Scorpion Anti-malware console and links the engine." OFF)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(SAM_CONSOLE_PROJECT_NAME "sam-console-debug")
    add_definitions(-DSAM_CONSOLE_DEBUG)
else()
    set(SAM_CONSOLE_PROJECT_NAME "sam-console")
endif()

set(SAM_CONSOLE_PROJECT_VERSION "1.0.0")
set(SAM_CONSOLE_PROJECT_DESCRIPTION "Scorpion Anti-malware Console")

project(${SAM_CONSOLE_PROJECT_NAME} VERSION ${SAM_CONSOLE_PROJECT_VERSION} LANGUAGES CXX)

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

set(SAM_CONSOLE_QT_VERSION "6")

file(GLOB SAM_CONSOLE_SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp 
)

# Find Qt
find_package(Qt${SAM_CONSOLE_QT_VERSION} COMPONENTS Core Widgets REQUIRED)

if (NOT LINK_CONSOLE)
    message(STATUS "Building the console without an engine...")
    add_executable(${SAM_CONSOLE_PROJECT_NAME} WIN32 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
        ${SAM_CONSOLE_SRC_FILES} 
    )

    message(STATUS "Linking Qt${SAM_CONSOLE_QT_VERSION} to the console...")
    target_link_libraries(${SAM_CONSOLE_PROJECT_NAME} PRIVATE 
        Qt${SAM_CONSOLE_QT_VERSION}::Widgets 
    )

    target_include_directories(${SAM_CONSOLE_PROJECT_NAME} PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/" 
    )

else()
    message(STATUS "Building the console as library...")
    set(SAM_CONSOLE_PROJECT_NAME ${SAM_CONSOLE_PROJECT_NAME} CACHE STRING "The name of the engine project.")
    add_library(${SAM_CONSOLE_PROJECT_NAME} SHARED STATIC 
        ${SAM_CONSOLE_SRC_FILES} 
    )

    message(STATUS "Linking Qt${SAM_CONSOLE_QT_VERSION} to the console...")
    # Link with public because we build the executable in the engine's CMakeLists.txt file.
    target_link_libraries(${SAM_CONSOLE_PROJECT_NAME} PUBLIC 
        Qt${SAM_CONSOLE_QT_VERSION}::Widgets 
    )

    target_include_directories(${SAM_CONSOLE_PROJECT_NAME} PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/" 
    )

endif()
