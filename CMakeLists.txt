cmake_minimum_required(VERSION 3.5)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(PROJECT_NAME "scorpion-antimalware-debug")
  add_definitions(-DSCORPION_ANTIMALWARE_DEBUG)
else()
  set(PROJECT_NAME "scorpion-antimalware")
endif()

set(PROJECT_DESCRIPTION "Scorpion Anti-malware")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

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

set(SCORPION_ANTIMALWARE_QT_VERSION "6")

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

# Find Qt
find_package(Qt${SCORPION_ANTIMALWARE_QT_VERSION} COMPONENTS Core Widgets REQUIRED)

add_executable(${PROJECT_NAME} WIN32 
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${SCORPION_ANTIMALWARE_QT_VERSION}::Widgets 
)
