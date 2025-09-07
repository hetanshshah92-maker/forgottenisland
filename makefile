# Makefile for Journey of the Forgotten Island
# C++ Text-Based Adventure Game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
DEBUG_FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g -DDEBUG

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/forgotten_island

# Source files
SOURCES = main.cpp Game.cpp GameInitialization.cpp Player.cpp Room.cpp Item.cpp

# Object files
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: directories $(TARGET)

# Create directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Build the main target
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	@$(CXX) $(OBJECTS) -o $@
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files
$(OBJ_DIR)/%.o: %.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS = $(DEBUG_FLAGS)
debug: directories $(TARGET)
	@echo "Debug build complete!"

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete!"

# Install (copy to /usr/local/bin)
install: $(TARGET)
	@echo "Installing $(TARGET)..."
	@sudo cp $(TARGET) /usr/local/bin/forgotten_island
	@sudo chmod +x /usr/local/bin/forgotten_island
	@echo "Installation complete! You can now run 'forgotten_island' from anywhere."

# Uninstall
uninstall:
	@echo "Uninstalling..."
	@sudo rm -f /usr/local/bin/forgotten_island
	@echo "Uninstall complete!"

# Run the game
run: $(TARGET)
	@echo "Starting Journey of the Forgotten Island..."
	@./$(TARGET)

# Run with debugging
run-debug: debug
	@echo "Starting game in debug mode..."
	@./$(TARGET)

# Package for distribution
package: clean all
	@echo "Creating distribution package..."
	@mkdir -p dist/forgotten_island
	@cp $(TARGET) dist/forgotten_island/
	@cp README.md dist/forgotten_island/ 2>/dev/null || echo "README.md not found, skipping..."
	@cp LICENSE dist/forgotten_island/ 2>/dev/null || echo "LICENSE not found, skipping..."
	@echo "#!/bin/bash" > dist/forgotten_island/run.sh
	@echo "./forgotten_island" >> dist/forgotten_island/run.sh
	@chmod +x dist/forgotten_island/run.sh
	@cd dist && tar -czf forgotten_island.tar.gz forgotten_island/
	@echo "Package created: dist/forgotten_island.tar.gz"

# Help target
help:
	@echo "Available targets:"
	@echo "  all         - Build the game (default)"
	@echo "  debug       - Build with debug symbols"
	@echo "  clean       - Remove build files"
	@echo "  run         - Build and run the game"
	@echo "  run-debug   - Build with debug and run"
	@echo "  install     - Install to system (requires sudo)"
	@echo "  uninstall   - Remove from system (requires sudo)"
	@echo "  package     - Create distribution package"
	@echo "  help        - Show this help message"

# Phony targets
.PHONY: all debug clean install uninstall run run-debug package help directories

# Dependencies (you can run 'make depend' to auto-generate these)
$(OBJ_DIR)/main.o: main.cpp Game.h
$(OBJ_DIR)/Game.o: Game.cpp Game.h Player.h Room.h Item.h
$(OBJ_DIR)/GameInitialization.o: GameInitialization.cpp Game.h
$(OBJ_DIR)/Player.o: Player.cpp Player.h Item.h
$(OBJ_DIR)/Room.o: Room.cpp Room.h Item.h
$(OBJ_DIR)/Item.o: Item.cpp Item.h