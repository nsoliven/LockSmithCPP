cmake_minimum_required(VERSION 3.22.1)

project(LockSmith VERSION 0.1.3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_VERBOSE_MAKEFILE ON)

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
target_link_libraries(lockSmithLib SQLiteCpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the executable
add_executable(lockSmithApp src/main.cpp)

# Link libraries to the executable
target_link_libraries(lockSmithApp PRIVATE lockSmithLib)

# Link additional libraries for UNIX
if(UNIX)
    target_link_libraries(lockSmithApp PRIVATE dl)
endif()
