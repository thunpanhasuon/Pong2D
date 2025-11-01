# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Raylib libraries
LIBS = -lraylib -lm -lpthread -ldl -lrt -lGL

# Directories
SRC_DIR = src
BIN_DIR = bin

# Files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OUT = $(BIN_DIR)/game

# Default target
all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

# Run the program
run: $(OUT)
	./$(OUT)

# Clean build files
clean:
	rm -rf $(BIN_DIR)

