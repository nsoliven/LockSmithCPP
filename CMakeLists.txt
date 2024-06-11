cmake_minimum_required(VERSION 3.22.1)

project(LockSmith VERSION 0.1.3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(OPENSSL_USE_STATIC_LIBS TRUE)

# Set our library files
set(lockSmithLibFiles 
    src/encryptionAlgorithm.cpp
    src/passwordManagement.cpp
    src/userInterface.cpp
)

# Create a static library
add_library(lockSmithLib STATIC ${lockSmithLibFiles})

# Create the executable
add_executable(lockSmithApp src/main.cpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectory for SQLiteCpp
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/SQLiteCpp)

# Find and include OpenSSL
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
  message(STATUS "OpenSSL Found: ${OPENSSL_VERSION}")
  message(STATUS "OpenSSL Include: ${OPENSSL_INCLUDE_DIR}")
  message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")

  target_include_directories(lockSmithLib PRIVATE ${OPENSSL_INCLUDE_DIR}) 

endif()

# Link libraries to the executable
target_link_libraries(lockSmithApp PRIVATE lockSmithLib OpenSSL::Crypto OpenSSL::SSL SQLiteCpp sqlite3 pthread)

# Link additional libraries for UNIX
if(UNIX)
    target_link_libraries(lockSmithApp PRIVATE dl)
endif()

# Include directories for SQLiteCpp
include_directories(lib/SQLiteCpp/include)
