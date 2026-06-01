CC = cc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude
AR = ar
ARFLAGS = rcs

BUILD = build
LIB = $(BUILD)/libdatastructures.a
SRCS = src/vector.c src/error.c
OBJS = $(BUILD)/vector.o $(BUILD)/error.o
TEST = $(BUILD)/vector_test

all: $(LIB) $(TEST)

$(BUILD)/vector.o: src/vector.c include/datastructures.h include/vector.h
	$(CC) $(CFLAGS) -c src/vector.c -o $(BUILD)/vector.o

$(BUILD)/error.o: src/error.c include/datastructures.h include/error.h
	$(CC) $(CFLAGS) -c src/error.c -o $(BUILD)/error.o

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

$(TEST): tests/test_vector.c $(LIB) include/datastructures.h
	$(CC) $(CFLAGS) tests/test_vector.c -L$(BUILD) -ldatastructures -o $(TEST)

clean:
	rm -rf $(BUILD)/*
