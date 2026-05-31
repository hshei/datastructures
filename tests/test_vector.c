#include "datastructures.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Test 1: char type - ALL OPERATIONS */
static void test_vector_char(void) {
    printf("\n=== Test: vector<char> - ALL OPERATIONS ===\n");
    vector_s *v = vector_init(sizeof(char));
    assert(v != NULL);

    // PUSH
    printf("  [PUSH] Adding 5 characters (H,e,l,l,o)...\n");
    char chars[] = {'H', 'e', 'l', 'l', 'o'};
    for (int i = 0; i < 5; i++) {
        assert(vector_push(v, &chars[i]) != NULL);
    }
    assert(v->size == 5);
    printf("    Size: %zu\n", v->size);

    // GET
    printf("  [GET] Retrieved at index 0: %c\n", *(char *)vector_get(v, 0));
    assert(*(char *)vector_get(v, 0) == 'H');

    // SET
    printf("  [SET] Setting index 1 to 'A'...\n");
    char setval = 'A';
    assert(vector_set(v, &setval, 1) != NULL);
    printf("    Value at index 1: %c\n", *(char *)vector_get(v, 1));
    assert(*(char *)vector_get(v, 1) == 'A');

    // INSERT
    printf("  [INSERT] Inserting 'X' at index 2...\n");
    char insval = 'X';
    assert(vector_insert(v, &insval, 2) != NULL);
    printf("    Size: %zu, String: ", v->size);
    for (size_t i = 0; i < v->size; i++) printf("%c", *(char *)vector_get(v, i));
    printf("\n");
    assert(v->size == 6);

    // REMOVE
    printf("  [REMOVE] Removing element at index 3...\n");
    assert(vector_remove(v, 3) != NULL);
    printf("    Size: %zu, String: ", v->size);
    for (size_t i = 0; i < v->size; i++) printf("%c", *(char *)vector_get(v, i));
    printf("\n");
    assert(v->size == 5);

    // POP
    printf("  [POP] Popping 2 elements...\n");
    assert(vector_pop(v) != NULL);
    assert(vector_pop(v) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 3);

    vector_free(v);
    printf("  OK\n");
}

/* Test 2: float type - ALL OPERATIONS */
static void test_vector_float(void) {
    printf("\n=== Test: vector<float> - ALL OPERATIONS ===\n");
    vector_s *v = vector_init(sizeof(float));
    assert(v != NULL);

    // PUSH
    printf("  [PUSH] Adding 4 floats (1.5, 2.5, 3.5, 4.5)...\n");
    float values[] = {1.5f, 2.5f, 3.5f, 4.5f};
    for (int i = 0; i < 4; i++) {
        assert(vector_push(v, &values[i]) != NULL);
    }
    assert(v->size == 4);
    printf("    Size: %zu\n", v->size);

    // GET
    printf("  [GET] Retrieved at index 1: %.1f\n", *(float *)vector_get(v, 1));
    assert(fabs(*(float *)vector_get(v, 1) - 2.5f) < 0.01f);

    // SET
    printf("  [SET] Setting index 0 to 9.9...\n");
    float setval = 9.9f;
    assert(vector_set(v, &setval, 0) != NULL);
    printf("    Value at index 0: %.1f\n", *(float *)vector_get(v, 0));
    assert(fabs(*(float *)vector_get(v, 0) - 9.9f) < 0.01f);

    // INSERT
    printf("  [INSERT] Inserting 7.7 at index 2...\n");
    float insval = 7.7f;
    assert(vector_insert(v, &insval, 2) != NULL);
    printf("    Size: %zu, Contents: [", v->size);
    for (size_t i = 0; i < v->size; i++) {
        printf("%.1f", *(float *)vector_get(v, i));
        if (i < v->size - 1) printf(", ");
    }
    printf("]\n");
    assert(v->size == 5);

    // REMOVE
    printf("  [REMOVE] Removing element at index 1...\n");
    assert(vector_remove(v, 1) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 4);

    // POP
    printf("  [POP] Popping 2 elements...\n");
    assert(vector_pop(v) != NULL);
    assert(vector_pop(v) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 2);

    vector_free(v);
    printf("  OK\n");
}

/* Test 3: double type - ALL OPERATIONS */
static void test_vector_double(void) {
    printf("\n=== Test: vector<double> - ALL OPERATIONS ===\n");
    vector_s *v = vector_init(sizeof(double));
    assert(v != NULL);

    // PUSH
    printf("  [PUSH] Adding 3 doubles (3.14159, 2.71828, 1.41421)...\n");
    double pi_approx[] = {3.14159265, 2.71828182, 1.41421356};
    for (int i = 0; i < 3; i++) {
        assert(vector_push(v, &pi_approx[i]) != NULL);
    }
    assert(v->size == 3);
    printf("    Size: %zu\n", v->size);

    // GET
    printf("  [GET] Retrieved at index 0: %.5f\n", *(double *)vector_get(v, 0));
    assert(fabs(*(double *)vector_get(v, 0) - 3.14159265) < 0.00001);

    // SET
    printf("  [SET] Setting index 2 to 2.0...\n");
    double setval = 2.0;
    assert(vector_set(v, &setval, 2) != NULL);
    printf("    Value at index 2: %.5f\n", *(double *)vector_get(v, 2));
    assert(fabs(*(double *)vector_get(v, 2) - 2.0) < 0.00001);

    // INSERT
    printf("  [INSERT] Inserting 1.5 at index 1...\n");
    double insval = 1.5;
    assert(vector_insert(v, &insval, 1) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 4);

    // REMOVE
    printf("  [REMOVE] Removing element at index 0...\n");
    assert(vector_remove(v, 0) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 3);

    // POP
    printf("  [POP] Popping 1 element...\n");
    assert(vector_pop(v) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 2);

    vector_free(v);
    printf("  OK\n");
}

/* Test 4: struct type (simple) - ALL OPERATIONS */
static void test_vector_struct_simple(void) {
    printf("\n=== Test: vector<struct> - ALL OPERATIONS ===\n");
    
    typedef struct {
        int id;
        float score;
    } student_t;

    vector_s *v = vector_init(sizeof(student_t));
    assert(v != NULL);

    // PUSH
    printf("  [PUSH] Adding 3 student structs...\n");
    student_t students[] = {
        {101, 85.5f},
        {102, 92.0f},
        {103, 78.5f},
    };
    for (int i = 0; i < 3; i++) {
        assert(vector_push(v, &students[i]) != NULL);
    }
    assert(v->size == 3);
    printf("    Size: %zu\n", v->size);

    // GET
    printf("  [GET] Retrieved at index 1: ID=%d, Score=%.1f\n",
           ((student_t *)vector_get(v, 1))->id,
           ((student_t *)vector_get(v, 1))->score);
    assert(((student_t *)vector_get(v, 1))->id == 102);

    // SET
    printf("  [SET] Setting index 0 to ID=999, Score=100.0...\n");
    student_t setval = {999, 100.0f};
    assert(vector_set(v, &setval, 0) != NULL);
    printf("    After set: ID=%d, Score=%.1f\n",
           ((student_t *)vector_get(v, 0))->id,
           ((student_t *)vector_get(v, 0))->score);
    assert(((student_t *)vector_get(v, 0))->id == 999);

    // INSERT
    printf("  [INSERT] Inserting ID=555, Score=88.5 at index 1...\n");
    student_t insval = {555, 88.5f};
    assert(vector_insert(v, &insval, 1) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 4);

    // REMOVE
    printf("  [REMOVE] Removing element at index 2...\n");
    assert(vector_remove(v, 2) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 3);

    // POP
    printf("  [POP] Popping 1 element...\n");
    assert(vector_pop(v) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 2);

    vector_free(v);
    printf("  OK\n");
}

/* Test 5: struct with array type - ALL OPERATIONS */
static void test_vector_struct_complex(void) {
    printf("\n=== Test: vector<complex struct> - ALL OPERATIONS ===\n");
    
    typedef struct {
        char name[20];
        int grades[5];
        size_t grade_count;
    } student_record_t;

    vector_s *v = vector_init(sizeof(student_record_t));
    assert(v != NULL);

    // PUSH
    printf("  [PUSH] Adding 2 complex student records...\n");
    student_record_t alice;
    strcpy(alice.name, "Alice");
    alice.grades[0] = 95;
    alice.grades[1] = 87;
    alice.grades[2] = 92;
    alice.grade_count = 3;

    student_record_t bob;
    strcpy(bob.name, "Bob");
    bob.grades[0] = 78;
    bob.grades[1] = 85;
    bob.grade_count = 2;

    assert(vector_push(v, &alice) != NULL);
    assert(vector_push(v, &bob) != NULL);
    assert(v->size == 2);
    printf("    Size: %zu\n", v->size);

    // GET
    printf("  [GET] Retrieved at index 0: %s\n", ((student_record_t *)vector_get(v, 0))->name);
    assert(strcmp(((student_record_t *)vector_get(v, 0))->name, "Alice") == 0);

    // SET
    printf("  [SET] Setting index 1 name to 'Charlie'...\n");
    student_record_t charlie;
    strcpy(charlie.name, "Charlie");
    charlie.grades[0] = 88;
    charlie.grades[1] = 88;
    charlie.grades[2] = 88;
    charlie.grade_count = 3;
    assert(vector_set(v, &charlie, 1) != NULL);
    printf("    After set: %s\n", ((student_record_t *)vector_get(v, 1))->name);
    assert(strcmp(((student_record_t *)vector_get(v, 1))->name, "Charlie") == 0);

    // INSERT
    printf("  [INSERT] Inserting new record at index 1...\n");
    student_record_t diana;
    strcpy(diana.name, "Diana");
    diana.grades[0] = 90;
    diana.grades[1] = 90;
    diana.grade_count = 2;
    assert(vector_insert(v, &diana, 1) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 3);

    // REMOVE
    printf("  [REMOVE] Removing element at index 0...\n");
    assert(vector_remove(v, 0) != NULL);
    printf("    Size: %zu, First name is now: %s\n", v->size, ((student_record_t *)vector_get(v, 0))->name);
    assert(v->size == 2);

    // POP
    printf("  [POP] Popping 1 element...\n");
    assert(vector_pop(v) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 1);

    vector_free(v);
    printf("  OK\n");
}

/* Test 6: pointer type - ALL OPERATIONS */
static void test_vector_pointer(void) {
    printf("\n=== Test: vector<pointer> - ALL OPERATIONS ===\n");
    
    vector_s *v = vector_init(sizeof(void *));
    assert(v != NULL);

    // PUSH
    printf("  [PUSH] Adding 3 void pointers to integers...\n");
    int vals[] = {10, 20, 30};
    void *p1 = &vals[0];
    void *p2 = &vals[1];
    void *p3 = &vals[2];
    assert(vector_push(v, &p1) != NULL);
    assert(vector_push(v, &p2) != NULL);
    assert(vector_push(v, &p3) != NULL);
    assert(v->size == 3);
    printf("    Size: %zu\n", v->size);

    // GET
    printf("  [GET] Retrieved at index 1, dereferenced: %d\n",
           *((int *)*(void **)vector_get(v, 1)));
    assert(*((int *)*(void **)vector_get(v, 1)) == 20);

    // SET
    printf("  [SET] Updating pointer at index 2...\n");
    int val_new = 333;
    void *ptr_new = &val_new;
    assert(vector_set(v, &ptr_new, 2) != NULL);
    printf("    Dereferenced: %d\n", *((int *)*(void **)vector_get(v, 2)));
    assert(*((int *)*(void **)vector_get(v, 2)) == 333);

    // INSERT
    printf("  [INSERT] Inserting pointer at index 1...\n");
    int val_ins = 111;
    void *ptr_ins = &val_ins;
    assert(vector_insert(v, &ptr_ins, 1) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 4);

    // REMOVE
    printf("  [REMOVE] Removing pointer at index 0...\n");
    assert(vector_remove(v, 0) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 3);

    // POP
    printf("  [POP] Popping 1 element...\n");
    assert(vector_pop(v) != NULL);
    printf("    Size: %zu\n", v->size);
    assert(v->size == 2);

    vector_free(v);
    printf("  OK\n");
}

/* Test 7: mixed operations on int type - ALL OPERATIONS */
static void test_vector_mixed_operations(void) {
    printf("\n=== Test: vector<int> - ALL OPERATIONS (comprehensive) ===\n");
    
    vector_s *v = vector_init(sizeof(int));
    assert(v != NULL);

    // PUSH 10 elements
    printf("  [PUSH] Adding 10 integers (1..10)...\n");
    for (int i = 1; i <= 10; i++) {
        assert(vector_push(v, &i) != NULL);
    }
    assert(v->size == 10);
    printf("    Size: %zu\n", v->size);

    // GET multiple elements
    printf("  [GET] Retrieved at indices 2, 5, 9: %d, %d, %d\n",
           *(int *)vector_get(v, 2),
           *(int *)vector_get(v, 5),
           *(int *)vector_get(v, 9));
    assert(*(int *)vector_get(v, 2) == 3);
    assert(*(int *)vector_get(v, 5) == 6);
    assert(*(int *)vector_get(v, 9) == 10);

    // SET an element
    printf("  [SET] Setting index 0 to 100...\n");
    int val = 100;
    assert(vector_set(v, &val, 0) != NULL);
    assert(*(int *)vector_get(v, 0) == 100);
    printf("    After set: %d\n", *(int *)vector_get(v, 0));
    
    // INSERT an element
    printf("  [INSERT] Inserting 50 at index 5...\n");
    int insert_val = 50;
    assert(vector_insert(v, &insert_val, 5) != NULL);
    assert(v->size == 11);
    printf("    Size after insert: %zu\n", v->size);

    // REMOVE an element
    printf("  [REMOVE] Removing element at index 3...\n");
    assert(vector_remove(v, 3) != NULL);
    assert(v->size == 10);
    printf("    Size after remove: %zu\n", v->size);

    // POP elements
    printf("  [POP] Popping 3 elements...\n");
    assert(vector_pop(v) != NULL);
    assert(vector_pop(v) != NULL);
    assert(vector_pop(v) != NULL);
    assert(v->size == 7);
    printf("    Size after pop: %zu\n", v->size);

    // Verify final state
    printf("  Final contents: [");
    for (size_t i = 0; i < v->size; i++) {
        printf("%d%s", *(int *)vector_get(v, i), i < v->size - 1 ? ", " : "");
    }
    printf("]\n");

    vector_free(v);
    printf("  OK\n");
}

int main(void) {
    printf("=== DATA STRUCTURES LIBRARY: TYPE INDEPENDENCE TESTS ===\n");
    
    test_vector_char();
    test_vector_float();
    test_vector_double();
    test_vector_struct_simple();
    test_vector_struct_complex();
    test_vector_pointer();
    test_vector_mixed_operations();
    
    printf("\nAll type independence tests passed.\n");
    return EXIT_SUCCESS;
}

