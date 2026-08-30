CC = g++
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g

TARGET = wc
TEST_SCRIPT = test.sh

SRC = wc.cpp
MAIN_SRC = main.cpp

OBJ = $(SRC:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

RELEASE_DIR = ./build/release
DEBUG_DIR = ./build/debug
TESTS_DIR = ./tests

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJ)
	mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -o $(RELEASE_DIR)/$(TARGET) $(MAIN_OBJ) $(OBJ)

test: $(TARGET)
	$(TESTS_DIR)/$(TEST_SCRIPT)
	
debug: $(MAIN_OBJ) $(OBJ)
	mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_DIR)/$(TARGET) $(MAIN_OBJ) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) *.o

.PHONY: all clean test debug
