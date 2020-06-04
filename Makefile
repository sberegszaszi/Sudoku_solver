ifeq ($(OS), Windows_NT)
	OS_NAME := Windows
else
	OS_NAME := $(shell uname)
endif

LOG_DIR := ./log
SRC_DIR := ./source
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR := ./bin
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
CXXFLAGS := -std=c++17 -Wall -Wextra -Wdeprecated -Weffc++ -pedantic -o2

ifeq ($(OS_NAME), Linux)
	CXX := /usr/bin/g++
	TARGET := Sudoku_solver
endif
ifeq ($(OS_NAME), Windows)
	CXX := g++
	TARGET := Sudoku_solver.exe
endif

.PHONY: all $(TARGET) $(OBJ_DIR)/%.o build_dir clean info

all: build_dir $(TARGET)

$(TARGET):  $(OBJ)
	$(CXX) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build_dir:
ifeq ($(OS_NAME), Linux)
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(LOG_DIR)
endif
ifeq ($(OS_NAME), Windows)
	@ if not exist $(subst /,\\,$(OBJ_DIR)) mkdir $(subst /,\\,$(OBJ_DIR))
	@ if not exist $(subst /,\\,$(LOG_DIR)) mkdir $(subst /,\\,$(LOG_DIR))
endif

clean:
ifeq ($(OS_NAME), Linux)
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)
endif
ifeq ($(OS_NAME), Windows)
	del $(subst /,\\,$(OBJ_DIR))\\*.o
	del $(TARGET)
endif

info:
	@echo OS: $(OS_NAME)
	@echo Source files: $(SRC)
	@echo Object files: $(OBJ)
	@echo Compiler: $(CXX)
	@echo Flags: $(CXXFLAGS)
	@echo Output: $(TARGET)