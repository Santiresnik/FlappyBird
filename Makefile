# Compiler and flags
CC := gcc
CFLAGS := -Wall -DLINUX -MMD -MP
LDFLAGS := -lncurses

# Directories
SRC_DIR := src
CORE_DIR := $(SRC_DIR)/core
#PLATFORM_DIR := $(SRC_DIR)/platform/linux
OBJ_DIR := obj/linux
BIN_DIR := bin/linux

# Executable name
TARGET := $(BIN_DIR)/flappybird

# Find all .c files
MAIN_SRC := $(SRC_DIR)/main.c
CORE_SRCS := $(wildcard $(CORE_DIR)/*.c)
#PLATFORM_SRCS := $(wildcard $(PLATFORM_DIR)/*.c)
SRCS := $(MAIN_SRC) $(CORE_SRCS) # $(PLATFORM_SRCS)

# Generate corresponding .o file paths
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)
# Default target
all: $(TARGET)

# Create output binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

# Compile each .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: 
	./$(TARGET)

print-vars:
	@echo "CC = $(CC)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "SRC_DIR = $(SRC_DIR)"
	@echo "CORE_DIR = $(CORE_DIR)"
#	@echo "PLATFORM_DIR = $(PLATFORM_DIR)"
	@echo "OBJ_DIR = $(OBJ_DIR)"
	@echo "BIN_DIR = $(BIN_DIR)"
	@echo "TARGET = $(TARGET)"
	@echo "MAIN_SRC = $(MAIN_SRC)"
	@echo "CORE_SRCS = $(CORE_SRCS)"
#	@echo "PLATFORM_SRCS = $(PLATFORM_SRCS)"
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"

.PHONY: all clean print-vars run

-include $(DEPS)