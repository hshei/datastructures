# 🚀 Generic Data Structures Library in C

A type-independent data structures library for C. Store **any data type** in the same container—ints, floats, structs, pointers, you name it. No macros, no template nonsense. Just solid C.

## What's Here?

**Vector** — A fully dynamic array that works with any data type. Push, pop, insert, remove, set, get. All the usual stuff.

```c
// Works with ANY type
vector_s *vec_ints;
vector_s *vec_floats;
vector_s *vec_students;

vector_init(&vec_ints, sizeof(int));
vector_init(&vec_floats, sizeof(float));
vector_init(&vec_students, sizeof(student_t));

// Same API for all types
int x = 42;
float pi = 3.14f;

vector_push(vec_ints, &x);
vector_push(vec_floats, &pi);
```

More data structures coming as we go.

## Build & Test

```sh
make            # Builds the library and tests
./build/vector_test   # Run the test suite
```

Tests cover **all 7 operations** (push, get, set, insert, remove, pop) on **7 different types**:
- char, float, double, int
- Simple struct, complex struct with nested arrays
- Void pointers

Everything passes. ✅

## Use It in Your Code

Compile your program:

```sh
cc -Wall -Wextra -std=c11 -Iinclude my_program.c -Lbuild -ldatastructures -o my_program
```

### Quick Start Example

```c
#include "datastructures.h"
#include <stdio.h>

int main() {
    vector_s *nums = NULL;
    
    // Create a vector for ints
    if (vector_init(&nums, sizeof(int)) != DS_OK) {
        fprintf(stderr, "Failed to create vector\n");
        return 1;
    }
    
    // Add some numbers
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        if (vector_push(nums, &values[i]) != DS_OK) {
            fprintf(stderr, "Push failed\n");
            vector_free(nums);
            return 1;
        }
    }
    
    // Get a value
    int result;
    if (vector_get(nums, 1, &result) != DS_OK) {
        fprintf(stderr, "Get failed\n");
        vector_free(nums);
        return 1;
    }
    printf("Value at index 1: %d\n", result);  // Output: 20
    
    vector_free(nums);
    return 0;
}
```

### More Examples

**Working with Floats:**

```c
vector_s *measurements = NULL;
vector_init(&measurements, sizeof(float));

float temp = 98.6f;
vector_push(measurements, &temp);

float read_back;
vector_get(measurements, 0, &read_back);
printf("Temperature: %.1f°F\n", read_back);

vector_free(measurements);
```

**Working with Structs:**

```c
typedef struct {
    char name[50];
    int age;
} person_t;

vector_s *people = NULL;
vector_init(&people, sizeof(person_t));

person_t alice = {"Alice", 30};
person_t bob = {"Bob", 25};

vector_push(people, &alice);
vector_push(people, &bob);

// Get someone back
person_t person;
vector_get(people, 0, &person);
printf("%s is %d years old\n", person.name, person.age);  // Output: Alice is 30 years old

vector_free(people);
```

**Modifying Elements:**

```c
vector_s *scores = NULL;
vector_init(&scores, sizeof(int));

int score = 85;
vector_push(scores, &score);

// Update the score at index 0
int new_score = 95;
vector_set(scores, &new_score, 0);

vector_get(scores, 0, &score);
printf("Updated score: %d\n", score);  // Output: 95

vector_free(scores);
```

**Inserting & Removing:**

```c
vector_s *data = NULL;
vector_init(&data, sizeof(int));

int vals[] = {1, 2, 4, 5};
for (int i = 0; i < 4; i++) {
    vector_push(data, &vals[i]);
}

// Insert 3 at index 2
int three = 3;
vector_insert(data, &three, 2);

// Remove element at index 0
vector_remove(data, 0);

// Pop from the end
int popped;
vector_pop(data, &popped);

vector_free(data);
```

## API Reference

### Initialization
```c
ds_err_t vector_init(vector_s **vector_out, size_t elem_size);
```
Creates a new vector that holds elements of size `elem_size`. Pass a pointer to your vector pointer.

### Inspection
```c
size_t vector_size(const vector_s *vector);      // How many elements are in it?
size_t vector_capacity(const vector_s *vector);  // How much space allocated?
```

### Adding Elements
```c
ds_err_t vector_push(vector_s *vector, void *element);           // Add to the end
ds_err_t vector_insert(vector_s *vector, void *element, size_t index);  // Insert at position
```

### Accessing Elements
```c
ds_err_t vector_get(vector_s *vector, size_t index, void *element_out);  // Read element
ds_err_t vector_set(vector_s *vector, void *element, size_t index);      // Replace element
```

### Removing Elements
```c
ds_err_t vector_pop(vector_s *vector, void *element_out);     // Remove from end
ds_err_t vector_remove(vector_s *vector, size_t index);       // Remove from position
```

### Cleanup
```c
ds_err_t vector_free(vector_s *vector);  // Free all memory
```

## Error Handling

All functions return a `ds_err_t` error code:
- `DS_OK` — Success
- `DS_ERR_ALLOC` — Memory allocation failed
- `DS_ERR_OUT_OF_BOUNDS` — Index out of range
- `DS_ERR_EMPTY` — Vector is empty
- `DS_ERR_INVALID_ARGUMENT` — Bad argument

Always check the return values! (See examples above.)

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
