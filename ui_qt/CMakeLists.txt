# Write configuration to config.h
set(UIQT_VERSION_MAJOR 0)
set(UIQT_VERSION_MINOR 1)

FIND_PACKAGE(Qt4 REQUIRED)

CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    )

# Build source list with enabled components
SET(UIQT_FILES MainWindow.cpp)
SET(UIQT_HEADERS MainWindow.h)

# Meta-object compiler pass
QT4_WRAP_CPP(UIQT_HEADERS_MOC ${UIQT_HEADERS})

# Includes and -D preprocessor definitions for Qt
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

# Build library
ADD_LIBRARY(uiqt ${UIQT_FILES} ${UIQT_HEADERS_MOC})
TARGET_LINK_LIBRARIES(uiqt ${QT_LIBRARIES})
