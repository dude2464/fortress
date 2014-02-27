# Write configuration to config.h
set(CORE_VERSION_MAJOR 0)
set(CORE_VERSION_MINOR 1)

CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    )

# Build source list with enabled components
SET(CORE_FILES core.cpp Fortress.cpp)

# Build library
ADD_LIBRARY(core ${CORE_FILES})
