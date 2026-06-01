# 🚀 Generic Data Structures Library in C

A type-independent data structures library for C. Store **any data type** in the same container—ints, floats, structs, pointers, you name it. No macros, no template nonsense. Just solid C.

## What's Here?

**Vector** — A fully dynamic array that works with any data type. Push, pop, insert, remove, set, get. All the usual stuff.

**Linked List** — A singly-linked list that works with any data type. Push front/back, pop front/back, insert, remove, get, set. Full control with no type constraints.

### Vector Examples

**Basic Usage with Integers:**

```c
vector_s *vec_ints = NULL;
vector_init(&vec_ints, sizeof(int));

int x = 42;
vector_push(vec_ints, &x);

int result;
vector_get(vec_ints, 0, &result);
printf("Value: %d\n", result);  // Output: 42

vector_free(vec_ints);
```

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
vector_push(people, &alice);

person_t person;
vector_get(people, 0, &person);
printf("%s is %d years old\n", person.name, person.age);

vector_free(people);
```

**Modifying and Removing Elements:**

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

### Linked List Examples

```c
// Initialize a linked list for integers
linked_list_s *list_ints;
llist_init(&list_ints, sizeof(int));

// Push elements to front and back
int a = 10, b = 20, c = 30;
llist_push_back(list_ints, &a);   // [10]
llist_push_back(list_ints, &b);   // [10, 20]
llist_push_front(list_ints, &c);  // [30, 10, 20]

// Get element at index
int result;
llist_get(list_ints, 1, &result);  // result = 10

// Insert at specific position
int x = 15;
llist_insert(list_ints, &x, 2);   // [30, 10, 15, 20]

// Remove element at index
llist_remove(list_ints, 0);       // [10, 15, 20]

// Pop from front/back
int popped;
llist_pop_back(list_ints, &popped);   // popped = 20
llist_pop_front(list_ints, &popped);  // popped = 10

// Clean up
llist_free(list_ints);
```

More data structures coming as we go.
