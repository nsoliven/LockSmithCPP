# Define the compiler
CC=g++

# Compiler flags, -g for debugging, -Wall for compiler warnings
CFLAGS=-g -Wall

# Include directory for header files
INCLUDES=-I.

# Linker flags for SQLite and OpenSSL libraries
LDFLAGS=-lsqlite3 -lcrypto -lssl

# Source files
SOURCES=main.cpp passwordmanagement.cpp userInterface.cpp encryptionAlgorithm.cpp

# Object files from SOURCES
OBJECTS=$(SOURCES:.cpp=.o)

# Output binary
EXECUTABLE=passmanager

# Default target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Rule for object files, how to make an .o from a .cpp
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean target to remove build artifacts
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Dependency rules for objects
main.o: main.cpp passwordmanagement.h userInterface.h
passwordmanagement.o: passwordmanagement.cpp passwordmanagement.h
userInterface.o: userInterface.cpp userInterface.h
encryptionAlgorithm.o: encryptionAlgorithm.cpp encryptionAlgorithm.h