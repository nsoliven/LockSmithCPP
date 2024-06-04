# Main CMake File for building the application

cmake_minimum_required(VERSION 3.22.1)

project(LockSmith VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


# set our library up
set(lockSmithLibFiles 
    src/encryptionAlgorithm.cpp
    src/passwordManagement.cpp
    src/userInterface.cpp
    )

add_library(lockSmithLib STATIC ${lockSmithLibFiles})

add_executable(lockSmithApp src/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/SQLiteCpp)



target_link_libraries(lockSmithApp lockSmithLib SQLiteCpp sqlite3 pthread)

if(UNIX)
    target_link_libraries(lockSmithApp PRIVATE dl)
endif()

include_directories(lib/SQLiteCpp/include)
