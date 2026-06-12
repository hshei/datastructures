# 🚀 Generic Data Structures Library in C

A type-independent data structures library for C. Store **any data type** in the same container—ints, floats, structs, pointers, you name it. No macros, no template nonsense. Just solid C.

## Understanding `void *` — C's Way of Generics

This library uses `void *` (void pointer) to achieve type-generic data structures. A `void *` is a pointer that can point to **any** data type—it's type-agnostic. 

**How it works:**

- When you push data, you pass a pointer to your value and the size of that type (`sizeof(int)`, `sizeof(float)`, etc.)
- The container stores a **copy** of your data (not the pointer itself) by using `memcpy()`
- When you retrieve data, you provide a pointer to where you want the data copied back out
- The size information you provided tells the container exactly how many bytes to copy

This approach means one set of code can handle integers, floats, structs, or any custom type without code duplication or complex macros.

## Getting Started

### Build the Library

```bash
cd datastructures
make
```

This compiles the library and creates object files in the `build/` directory.

### Use in Your Project

1. **Include the header:**

   ```c
   #include "datastructures.h"
   ```

2. **Link against the library:**
   When compiling your program, link the data structure object files:

   ```bash
   gcc your_program.c datastructures/src/vector.c datastructures/src/linked_list.c datastructures/src/hashmap.c -I datastructures/include -o your_program
   ```

3. **Or use the Makefile:**
   Add your source file to the Makefile and run `make`.

### Error Handling

All functions return a `ds_err_t` status code:

- `DS_OK` — Operation succeeded
- `DS_ERR_ALLOC` — Memory allocation failed
- `DS_ERR_NOT_FOUND` — Element or key not found
- `DS_ERR_OUT_OF_BOUNDS` — Index out of bounds
- `DS_ERR_EMPTY` — Attempted operation on empty container
- `DS_ERR_INVALID_ARGUMENT` — Invalid argument passed

Use `ds_err_str()` to get a readable error message:

```c
ds_err_t err = vector_pop(vec, &result);
if (err != DS_OK) {
    fprintf(stderr, "Error: %s\n", ds_err_str(err));
}
```

## Data Structures

### Vector

A **dynamic array** that grows as needed. Access elements by index in O(1) time.

**Functions:**

- `vector_init()` — Create a new vector with a given element size
- `vector_push()` — Add element to the end
- `vector_pop()` — Remove and retrieve element from the end
- `vector_insert()` — Insert element at a specific index
- `vector_remove()` — Remove element at a specific index
- `vector_get()` — Retrieve element at a specific index
- `vector_set()` — Update element at a specific index
- `vector_free()` — Free all memory

### Linked List

A **singly-linked list** that can efficiently insert/remove from both ends.

**Functions:**

- `llist_init()` — Create a new linked list with a given element size
- `llist_push_front()` — Add element to the front
- `llist_push_back()` — Add element to the end
- `llist_pop_front()` — Remove and retrieve element from the front
- `llist_pop_back()` — Remove and retrieve element from the end
- `llist_insert()` — Insert element at a specific index
- `llist_remove()` — Remove element at a specific index
- `llist_get()` — Retrieve element at a specific index
- `llist_set()` — Update element at a specific index
- `llist_free()` — Free all memory

### HashMap

A **hash table** for fast key-value lookups. Store and retrieve values by key in O(1) average time.

**Functions:**

- `hm_init()` — Create a new hash map with given key size, value size, and bucket count
- `hm_insert()` — Insert or update a key-value pair
- `hm_get()` — Retrieve value by key
- `hm_remove()` — Remove a key-value pair
- `hm_free()` — Free all memory

---

## Examples

### Vector

```c
// Store integers
vector_s *vec = NULL;
vector_init(&vec, sizeof(int));

int values[] = {1, 2, 4, 5};
for (int i = 0; i < 4; i++) {
    vector_push(vec, &values[i]);
}

// Insert 3 at index 2
int three = 3;
vector_insert(vec, &three, 2);

// Retrieve element
int result;
vector_get(vec, 2, &result);  // result = 3

vector_free(vec);
```

### Linked List

```c
// Store floats
linked_list_s *list = NULL;
llist_init(&list, sizeof(float));

float x = 3.14f, y = 2.71f;
llist_push_back(list, &x);
llist_push_back(list, &y);

// Get element at index 0
float first;
llist_get(list, 0, &first);  // first = 3.14f

llist_free(list);
```

### HashMap

```c
// Map string keys to integer values
hashmap_s *map = NULL;
hm_init(&map, sizeof(int), sizeof(int), 16);  // key_size=10, value_size=sizeof(int), bucket_count=16

char key1[10] = "count";
int value1 = 42;
hm_insert(map, key1, &value1);

// Retrieve value
int retrieved;
hm_get(map, key1, &retrieved);  // retrieved = 42

hm_free(map);
```

---

## Performance Benchmarks

Benchmark results running on **Mac Mini M4 with 16GB RAM** using **-O2 optimization**:

### Vector

```txt
push_back x100k                                            0.701 ms  (100000 ops)
sequential get x100k                                       0.601 ms  (100000 ops)
random get x100k                                           1.127 ms  (100000 ops)
middle insert x10k                                         9.491 ms  (10000 ops)
pop xMEDIUM (draining)                                     0.090 ms  (0 ops)
```

### Linked List

```txt
push_back x100k                                            5.288 ms  (100000 ops)
push_front x10k                                            0.477 ms  (10000 ops)
sequential get x1k                                         1.100 ms  (1000 ops)
middle insert x1k                                         57.835 ms  (1000 ops)
pop_front x100k (draining)                                 1.813 ms  (0 ops)
```

### Vector vs Linked List — Head-to-Head

```txt
Operation                                                     Vector   LinkedList
push_back x100k                                               0.319ms       1.914ms
sequential get x1k                                            0.003ms       0.140ms
middle insert x1k                                             0.034ms       0.577ms
pop_front x10k                                                1.923ms       0.151ms
```

### Hashmap

```txt
--- 1k entries ---
insert x1000 (buckets=16)                                  0.047 ms  (1000 ops)
get x1000 (buckets=16)                                     0.007 ms  (1000 ops)
remove x1000 (buckets=16)                                  0.032 ms  (1000 ops)

--- 10k entries ---
insert x10000 (buckets=16)                                 0.354 ms  (10000 ops)
get x10000 (buckets=16)                                    0.068 ms  (10000 ops)
remove x10000 (buckets=16)                                 0.280 ms  (10000 ops)

--- 100k entries ---
insert x100000 (buckets=16)                                5.350 ms  (100000 ops)
get x100000 (buckets=16)                                   1.243 ms  (100000 ops)
remove x100000 (buckets=16)                                2.785 ms  (100000 ops)

--- rehash effect: fixed buckets vs auto-rehash ---
insert x100k (fixed=128)                                      3.853ms
insert x100k (fixed=16, rehash)                               4.544ms
final bucket_count                                           262144
```

