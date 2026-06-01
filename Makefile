CC = cc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude
AR = ar
ARFLAGS = rcs

BUILD = build
LIB = $(BUILD)/libdatastructures.a
SRCS = src/vector.c src/error.c src/linked_list.c
OBJS = $(BUILD)/vector.o $(BUILD)/error.o $(BUILD)/linked_list.o
TESTS = $(BUILD)/vector_test $(BUILD)/linked_list_test

all: $(LIB) $(TESTS)

$(BUILD)/vector.o: src/vector.c include/datastructures.h include/vector.h
	$(CC) $(CFLAGS) -c src/vector.c -o $(BUILD)/vector.o

$(BUILD)/error.o: src/error.c include/datastructures.h include/error.h
	$(CC) $(CFLAGS) -c src/error.c -o $(BUILD)/error.o

$(BUILD)/linked_list.o: src/linked_list.c include/datastructures.h include/linked_list.h
	$(CC) $(CFLAGS) -c src/linked_list.c -o $(BUILD)/linked_list.o

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

$(BUILD)/vector_test: tests/test_vector.c $(LIB) include/datastructures.h
	$(CC) $(CFLAGS) tests/test_vector.c -L$(BUILD) -ldatastructures -o $(BUILD)/vector_test

$(BUILD)/linked_list_test: tests/test_linked_list.c $(LIB) include/datastructures.h
	$(CC) $(CFLAGS) tests/test_linked_list.c -L$(BUILD) -ldatastructures -o $(BUILD)/linked_list_test

clean:
	rm -rf $(BUILD)/*
