CC = g++
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g
TARGET = wc
TEST_SCRIPT = test.sh
SRC = wc.cpp
MAIN_SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) $(OBJ)

test: $(TARGET)
	./$(TEST_SCRIPT)
	
debug: $(MAIN_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET) $(MAIN_OBJ) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: all clean test debug
