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

set(SAM_CONSOLE_PROJECT_NAME "sam-console")

set(SAM_CONSOLE_PROJECT_VERSION "1.0.0")
set(SAM_CONSOLE_PROJECT_DESCRIPTION "Scorpion Anti-malware Console.")

project(${SAM_CONSOLE_PROJECT_NAME} VERSION ${SAM_CONSOLE_PROJECT_VERSION} LANGUAGES CXX)

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

# Safety check: Ensure that all the files exist.
foreach(file ${SAM_CONSOLE_MAIN_ENTRY})
if(NOT EXISTS "${file}")
    message(FATAL_ERROR "File '${file}' does not exist!")
endif()
endforeach()

file(GLOB SAM_CONSOLE_SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/controlbar.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/controlbar.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/scanbutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/scanbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/stopbutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/stopbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/pausebutton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control-bar/pausebutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/statusviewer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/statusviewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/summary.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/status-viewer/summary.cpp
)

# Safety check: Ensure that all the files exist.
foreach(file ${SAM_CONSOLE_SRC_FILES})
    if(NOT EXISTS "${file}")
        message(FATAL_ERROR "File '${file}' does not exist!")
    endif()
endforeach()

if (NOT SAM_LINK_CONSOLE)
    # If the engine did not request to link the console, use the dummy engine.

    message(STATUS "Building the console without an engine...")
    # TODO: Is this Windows specific?

    # Find Qt
    # TODO: Move this find package outside the if statement.
    find_package(Qt${SAM_CONSOLE_QT_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets)

    add_executable(${SAM_CONSOLE_PROJECT_NAME} WIN32 
        ${SAM_CONSOLE_MAIN_ENTRY} 
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

    # Link the dummy engine.
    message(STATUS "Linking the dummy engine to the console...")
    set(SAM_DUMMY_ENGINE_ROOTDIR "${SAM_CONSOLE_ROOTDIR}/sam-dummy-engine")
    add_subdirectory(${SAM_DUMMY_ENGINE_ROOTDIR})

    target_link_libraries(${SAM_CONSOLE_PROJECT_NAME} PRIVATE 
        ${SAM_DUMMY_ENGINE}
    )

    # Specify the directory containing the shared libraries.
    set(SAM_DUMMY_ENGINE_BUILD_ROOTDIR "${PROJECT_BINARY_DIR}/sam-dummy-engine")
    
    # TODO: Why copy_if_different isn't working?
    # Copy the shared libraries to the executable directory.
    file(GLOB SAM_DUMMY_ENGINE_DLLS 
        "${SAM_DUMMY_ENGINE_BUILD_ROOTDIR}/Debug/${SAM_DUMMY_ENGINE}.dll"
    )

    # Safety check: Ensure that all the files exist.
    foreach(file ${SAM_DUMMY_ENGINE_DLLS})
        if(NOT EXISTS "${file}")
            message(FATAL_ERROR "File '${file}' does not exist!")
        endif()
    endforeach()

    foreach(SAM_DUMMY_ENGINE_DLL ${SAM_DUMMY_ENGINE_DLLS})
        add_custom_command(TARGET ${SAM_CONSOLE_PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy ${SAM_DUMMY_ENGINE_DLL} $<TARGET_FILE_DIR:${SAM_CONSOLE_PROJECT_NAME}>
                        COMMENT "Copying ${SAM_DUMMY_ENGINE_DLL} to the executable directory."
        )
    endforeach()

else()
    # If the engine requested to link the console.

    set(SAM_CONSOLE_QT_VERSION ${SAM_CONSOLE_QT_VERSION} CACHE INTERNAL "Sam Console Qt Version" FORCE) 

    # Cache the main entry files to be used in parent CMakeLists.txt file.
    set(SAM_CONSOLE_MAIN_ENTRY ${SAM_CONSOLE_MAIN_ENTRY} CACHE INTERNAL "Sam Console Main Entry" FORCE)
    set(SAM_CONSOLE_SRC_FILES ${SAM_CONSOLE_SRC_FILES} CACHE INTERNAL "Sam Console Source Files" FORCE)

endif()

#################################################
#
# Scorpion Anti-malware Console Tests
#
#################################################

if (SAM_CONSOLE_BUILD_TESTS)
    message(STATUS "Building Scorpion Anti-malware console tests...")
    set(SAM_CONSOLE_TESTS_ROOTDIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    add_subdirectory(${SAM_CONSOLE_TESTS_ROOTDIR})
endif()
