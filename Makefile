CC = cc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude
AR = ar
ARFLAGS = rcs

BUILD = build
LIB = $(BUILD)/libdatastructures.a
SRC = src/Vector.c
OBJ = $(BUILD)/Vector.o
TEST = $(BUILD)/vector_test

all: $(LIB) $(TEST)

$(OBJ): $(SRC) include/datastructures.h include/vector.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

$(TEST): tests/test_vector.c $(LIB) include/datastructures.h
	$(CC) $(CFLAGS) tests/test_vector.c -L$(BUILD) -ldatastructures -o $(TEST)

clean:
	rm -rf $(BUILD)/*
