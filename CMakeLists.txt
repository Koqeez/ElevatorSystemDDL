cmake_minimum_required(VERSION 3.10)
project(ElevatorSystemDDL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add platform-specific compile definitions
if(WIN32)
    add_definitions(-D_WIN32)
endif()

# Add Unix-specific compile options
if(UNIX)
    add_compile_options(-Wall -Wextra)
endif()

# Define source files
set(SOURCES
    "Source Files/SimulationTime.cpp"
    "Source Files/Algorytm.cpp"
    "Source Files/DataManagement.cpp"
    "Source Files/Display.cpp"
    "Source Files/DispatcherUnit.cpp"
    "Source Files/ElevatorCar.cpp"
    "Source Files/Floor.cpp"
    "Source Files/Menu.cpp"
    "Source Files/Zapytania.cpp"
    "Source Files/PlatformUtils.cpp"
)

# Define header files
set(HEADERS
    "Header Files/Algorytm.h"
    "Header Files/DataManagement.h"
    "Header Files/DispatcherUnit.h"
    "Header Files/ElevatorCar.h"
    "Header Files/Floor.h"
    "Header Files/GlobalVariables.h"
    "Header Files/Menu.h"
    "Header Files/SimulationTime.h"
    "Header Files/Zapytania.h"
    "Header Files/PlatformUtils.h"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE "Header Files")

# Set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Copy resource files to build directory
file(COPY "Resource Files" DESTINATION "${CMAKE_BINARY_DIR}/bin"
     PATTERN "*"
     PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
file(RENAME "${CMAKE_BINARY_DIR}/bin/Resource Files" "${CMAKE_BINARY_DIR}/bin/ResourceFiles")

message(STATUS "Resource Files will be copied to: ${CMAKE_BINARY_DIR}/bin/ResourceFiles")
