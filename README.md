# 🚀 Generic Data Structures Library in C

A type-independent data structures library for C. Store **any data type** in the same container—ints, floats, structs, pointers, you name it.

## What's Here?

**Vector** — A fully dynamic array that works with any data type. Push, pop, insert, remove, set, get. All the usual stuff.

```c
// Works with ANY type
vector_s *vec_ints = vector_init(sizeof(int));
vector_s *vec_floats = vector_init(sizeof(float));
vector_s *vec_students = vector_init(sizeof(student_t));

// Same functions for all types
vector_push(vec_ints, &my_int);
vector_push(vec_floats, &my_float);
vector_push(vec_students, &my_student);
```

More data structures coming as we go.

## Build It

```sh
make
```

Creates:
- `build/libdatastructures.a` — the library
- `build/vector_test` — test executable

## Run the Tests

```sh
./build/vector_test
```

Tests cover **all 7 operations** (push, get, set, insert, remove, pop) on **7 different types**:
- char, float, double
- Simple struct, complex struct with nested arrays
- Void pointers
- Integers

Everything passes. ✅

## Use It in Your Code

Link against the library:

```sh
cc -Wall -Wextra -std=c11 -Iinclude my_program.c -Lbuild -ldatastructures -o my_program
```

In your code:

```c
#include "datastructures.h"

int main() {
    vector_s *v = vector_init(sizeof(int));
    
    int x = 42;
    vector_push(v, &x);
    
    int *result = (int *)vector_get(v, 0);
    printf("Got: %d\n", *result);
    
    vector_free(v);
    return 0;
}
```

## Architecture

```
src/              — Implementation
include/          — Public headers
tests/            — Test files
build/            — Compiled objects and archives (generated)
Makefile          — Build automation
```

Each data structure gets its own `.c` and `.h` pair. New structures are included in `include/datastructures.h` so you only need to `#include "datastructures.h"`.

## Adding More Data Structures

1. Create `src/NewStructure.c` and `include/newstructure.h`
2. Implement your structure following the vector pattern
3. Add `#include "newstructure.h"` to `include/datastructures.h`
4. Update the Makefile to compile your `.c` file
5. Create `tests/test_newstructure.c`

## Push to GitHub (When Ready)

```sh
git init
git add .
git commit -m "Type-independent data structures library"
git remote add origin https://github.com/<hshei>/datastructures.git
git branch -M main
git push -u origin main
```
