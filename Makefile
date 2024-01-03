CC = cc
CFLAGS = -Wall -Wextra -ggdb -pedantic
INC_DIR = src
SRC_DIR = test
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
EXECUTABLES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))
all: $(EXECUTABLES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/*.c $< -o $@

$(OBJ_DIR)/%.o: 
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(INC_DIR)/*.c -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

