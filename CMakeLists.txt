cmake_minimum_required(VERSION 3.22.1)

project(LockSmith VERSION 0.1.3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Prefer static libraries
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)

# Set static flag for all platforms
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# Special static linking flags for Unix-like systems (Linux and macOS)
if(UNIX AND NOT MINGW)
    # Avoid using -static with glibc to prevent dlopen issues
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Special static linking for Windows (MinGW)
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# Add subdirectory for SQLiteCpp
find_package(SQLiteCpp REQUIRED)
find_package(botan REQUIRED)

# Set our library files
set(lockSmithLibFiles 
    src/encryptionAlgorithm.cpp
    src/passwordManagement.cpp
    src/userInterface.cpp
)

# Create a static library
add_library(lockSmithLib STATIC ${lockSmithLibFiles})
target_link_libraries(lockSmithLib SQLiteCpp botan::botan SQLite::SQLite3)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the executable
add_executable(lockSmithApp src/main.cpp)

# Link libraries to the executable
target_link_libraries(lockSmithApp PRIVATE lockSmithLib)

# Special static linking for Windows (MinGW) libraries
if(MINGW)
    target_link_libraries(lockSmithApp PRIVATE -static -static-libgcc -static-libstdc++)
endif()