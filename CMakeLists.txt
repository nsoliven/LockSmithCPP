cmake_minimum_required(VERSION 3.22.1)

enable_testing()

project(LockSmith VERSION 0.1.3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prefer static libraries (work for Linux)
if(NOT APPLE)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
endif()

# Set static flags for all platforms
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Special static linking flags for Linux
if(UNIX AND NOT APPLE AND NOT MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Special static linking for Windows (MinGW)
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# Add subdirectory for SQLiteCpp
find_package(SQLiteCpp REQUIRED)
find_package(botan REQUIRED)
find_package(GTest REQUIRED)

# Set our library files
set(lockSmithLibFiles 
    src/encryptionAlgorithm.cpp
    src/passwordManagement.cpp
    src/userInterface.cpp
)


# Create a static library
add_library(lockSmithLib STATIC ${lockSmithLibFiles})
target_link_libraries(lockSmithLib SQLiteCpp botan::botan SQLite::SQLite3)
target_link_libraries(lockSmithLib GTest::GTest GTest::Main)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the executable
add_executable(lockSmithApp src/main.cpp)
add_executable(lockSmithEncryptionTest tests/test_encryptionAlgorithm.cpp)
add_executable(lockSmithPasswordManagement tests/test_passwordManagement.cpp)

# Link libraries to the executable
target_link_libraries(lockSmithApp PRIVATE lockSmithLib)
target_link_libraries(lockSmithEncryptionTest lockSmithLib)
target_link_libraries(lockSmithPasswordManagement lockSmithLib)

# Special static linking for Windows (MinGW) libraries
if(MINGW)
    target_link_libraries(lockSmithApp PRIVATE -static -static-libgcc -static-libstdc++)
endif()

# Add tests to CTest
add_test(NAME lockSmithEncryptionTest COMMAND lockSmithEncryptionTest)
add_test(NAME lockSmithPasswordManagementTest COMMAND lockSmithPasswordManagement)