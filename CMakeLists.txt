CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")
PROJECT(fortress)

# Works around silly limitations in CMake
SET(EMPTY_FILE ${CMAKE_BINARY_DIR}/dummy.c)
file(WRITE ${EMPTY_FILE} "")

# Sets up project-wide include dirs
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

# Recursively builds core component
ADD_SUBDIRECTORY(core)

# Qt interface
OPTION(BUILD_QT_UI "Build the Qt UI (requires Qt and QtGui)" OFF)
IF(BUILD_QT_UI)
    ADD_SUBDIRECTORY(ui_qt)
    ADD_EXECUTABLE(fortress_qt ${EMPTY_FILE})
    TARGET_LINK_LIBRARIES(fortress_qt uiqt core)
ENDIF()
