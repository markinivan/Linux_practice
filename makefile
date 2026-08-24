CC = g++
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g
TARGET = wc
TEST_TARGET = run_tests
SRC = wc.cpp
TEST_SRC = tests.cpp
MAIN_SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) $(OBJ)

$(TEST_TARGET): $(TEST_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) $(OBJ)

test: $(TEST_TARGET)
	./$(TEST_TARGET)
	
debug: $(MAIN_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET) $(MAIN_OBJ) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: all clean test debug
