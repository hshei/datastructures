#include "datastructures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────────────────
   Helpers
───────────────────────────────────────────── */

static int tests_run    = 0;
static int tests_passed = 0;

#define TEST(name) \
    do { \
        printf("  %-60s", name); \
        tests_run++; \
    } while(0)

#define PASS() \
    do { \
        printf("PASS\n"); \
        tests_passed++; \
    } while(0)

#define FAIL(msg) \
    do { \
        printf("FAIL  (%s:%d) %s\n", __FILE__, __LINE__, msg); \
    } while(0)

#define CHECK(cond, msg) \
    do { \
        if (!(cond)) { FAIL(msg); return; } \
    } while(0)

/* ─────────────────────────────────────────────
   Custom structs
───────────────────────────────────────────── */

typedef struct { int x; int y; } Point;
typedef struct { char name[32]; int age; } Person;

static Point make_point(int x, int y) { Point p = {x, y}; return p; }
static Person make_person(const char *name, int age) {
    Person p;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    p.age = age;
    return p;
}

/* ═══════════════════════════════════════════
   TEST GROUPS
═══════════════════════════════════════════ */

/* ── 1. Init / Free ─────────────────────── */

static void test_init_basic(void) {
    TEST("init: basic initialisation");
    hashmap_s *hm = NULL;
    CHECK(hm_init(&hm, sizeof(int), sizeof(int), 16) == DS_OK, "init failed");
    CHECK(hm != NULL,               "hm is NULL");
    CHECK(hm->size == 0,            "size != 0");
    CHECK(hm->bucket_count == 16,   "bucket_count != 16");
    CHECK(hm->buckets != NULL,      "buckets is NULL");
    hm_free(hm);
    PASS();
}

static void test_init_all_buckets_null(void) {
    TEST("init: all buckets initialised to NULL");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    for (size_t i = 0; i < 16; i++)
        CHECK(hm->buckets[i] == NULL, "bucket not NULL after init");
    hm_free(hm);
    PASS();
}

static void test_free_empty(void) {
    TEST("free: empty hashmap is safe");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    CHECK(hm_free(hm) == DS_OK, "free empty failed");
    PASS();
}

/* ── 2. Insert / Get ────────────────────── */

static void test_insert_and_get_int(void) {
    TEST("insert/get: int key, int value");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 42, value = 100;
    CHECK(hm_insert(hm, &key, &value) == DS_OK, "insert failed");
    CHECK(hm->size == 1, "size != 1");
    int out = 0;
    CHECK(hm_get(hm, &key, &out) == DS_OK, "get failed");
    CHECK(out == 100, "value wrong");
    hm_free(hm);
    PASS();
}

static void test_insert_and_get_multiple(void) {
    TEST("insert/get: multiple int key-value pairs");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    for (int i = 0; i < 10; i++)
        CHECK(hm_insert(hm, &i, &i) == DS_OK, "insert failed");
    CHECK(hm->size == 10, "size != 10");
    for (int i = 0; i < 10; i++) {
        int out = -1;
        CHECK(hm_get(hm, &i, &out) == DS_OK, "get failed");
        CHECK(out == i, "value mismatch");
    }
    hm_free(hm);
    PASS();
}

static void test_insert_point_key(void) {
    TEST("insert/get: Point struct as key");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(Point), sizeof(int), 16);
    Point key = make_point(3, 7);
    int value = 99;
    CHECK(hm_insert(hm, &key, &value) == DS_OK, "insert failed");
    int out = 0;
    CHECK(hm_get(hm, &key, &out) == DS_OK, "get failed");
    CHECK(out == 99, "value wrong");
    hm_free(hm);
    PASS();
}

static void test_insert_person_value(void) {
    TEST("insert/get: Person struct as value");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(Person), 16);
    int key = 1;
    Person value = make_person("Alice", 30);
    CHECK(hm_insert(hm, &key, &value) == DS_OK, "insert failed");
    Person out; memset(&out, 0, sizeof(out));
    CHECK(hm_get(hm, &key, &out) == DS_OK, "get failed");
    CHECK(strcmp(out.name, "Alice") == 0, "name wrong");
    CHECK(out.age == 30, "age wrong");
    hm_free(hm);
    PASS();
}

static void test_insert_duplicate_key(void) {
    TEST("insert/get: duplicate key inserts both, get returns first");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 1, val1 = 10, val2 = 20;
    hm_insert(hm, &key, &val1);
    hm_insert(hm, &key, &val2);
    CHECK(hm->size == 2, "size != 2");
    /* get returns the most recently inserted (front of chain) */
    int out = 0;
    hm_get(hm, &key, &out);
    CHECK(out == val2, "expected most recent value");
    hm_free(hm);
    PASS();
}

static void test_get_missing_key(void) {
    TEST("get: missing key returns DS_ERR_NOT_FOUND");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 42, out = 0;
    CHECK(hm_get(hm, &key, &out) == DS_ERR_NOT_FOUND, "expected NOT_FOUND");
    hm_free(hm);
    PASS();
}

static void test_get_empty_bucket(void) {
    TEST("get: key hashes to empty bucket returns DS_ERR_NOT_FOUND");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key1 = 1, val = 10;
    hm_insert(hm, &key1, &val);
    int key2 = 999, out = 0;
    CHECK(hm_get(hm, &key2, &out) == DS_ERR_NOT_FOUND, "expected NOT_FOUND");
    hm_free(hm);
    PASS();
}

/* ── 3. Remove ──────────────────────────── */

static void test_remove_basic(void) {
    TEST("remove: existing key removed, size decremented");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 1, val = 10;
    hm_insert(hm, &key, &val);
    CHECK(hm_remove(hm, &key) == DS_OK, "remove failed");
    CHECK(hm->size == 0, "size != 0");
    int out = 0;
    CHECK(hm_get(hm, &key, &out) == DS_ERR_NOT_FOUND, "key still present after remove");
    hm_free(hm);
    PASS();
}

static void test_remove_missing_key(void) {
    TEST("remove: missing key returns DS_ERR_NOT_FOUND");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 99;
    CHECK(hm_remove(hm, &key) == DS_ERR_NOT_FOUND, "expected NOT_FOUND");
    hm_free(hm);
    PASS();
}

static void test_remove_empty_bucket(void) {
    TEST("remove: key hashes to empty bucket returns DS_ERR_NOT_FOUND");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key1 = 1, val = 10;
    hm_insert(hm, &key1, &val);
    int key2 = 999;
    CHECK(hm_remove(hm, &key2) == DS_ERR_NOT_FOUND, "expected NOT_FOUND");
    hm_free(hm);
    PASS();
}

static void test_remove_head_of_chain(void) {
    TEST("remove: head of chain, rest of chain intact");
    hashmap_s *hm = NULL;
    /* bucket_count=1 forces all keys into same bucket */
    hm_init(&hm, sizeof(int), sizeof(int), 1);
    int k1 = 1, k2 = 2, k3 = 3, v = 10;
    hm_insert(hm, &k1, &v); v = 20;
    hm_insert(hm, &k2, &v); v = 30;
    hm_insert(hm, &k3, &v);
    /* k3 is at head since we insert at front */
    CHECK(hm_remove(hm, &k3) == DS_OK, "remove head failed");
    CHECK(hm->size == 2, "size wrong");
    int out = 0;
    CHECK(hm_get(hm, &k1, &out) == DS_OK && out == 10, "k1 lost after head remove");
    CHECK(hm_get(hm, &k2, &out) == DS_OK && out == 20, "k2 lost after head remove");
    hm_free(hm);
    PASS();
}

static void test_remove_middle_of_chain(void) {
    TEST("remove: middle of chain, neighbours intact");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 1);
    int k1 = 1, k2 = 2, k3 = 3, v = 10;
    hm_insert(hm, &k1, &v); v = 20;
    hm_insert(hm, &k2, &v); v = 30;
    hm_insert(hm, &k3, &v);
    CHECK(hm_remove(hm, &k2) == DS_OK, "remove middle failed");
    CHECK(hm->size == 2, "size wrong");
    int out = 0;
    CHECK(hm_get(hm, &k1, &out) == DS_OK, "k1 lost");
    CHECK(hm_get(hm, &k3, &out) == DS_OK, "k3 lost");
    CHECK(hm_get(hm, &k2, &out) == DS_ERR_NOT_FOUND, "k2 still present");
    hm_free(hm);
    PASS();
}

static void test_remove_then_reinsert(void) {
    TEST("remove: removed key can be reinserted");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 5, val = 50;
    hm_insert(hm, &key, &val);
    hm_remove(hm, &key);
    val = 99;
    CHECK(hm_insert(hm, &key, &val) == DS_OK, "reinsert failed");
    int out = 0;
    CHECK(hm_get(hm, &key, &out) == DS_OK, "get after reinsert failed");
    CHECK(out == 99, "value wrong after reinsert");
    hm_free(hm);
    PASS();
}

/* ── 4. Collisions ──────────────────────── */

static void test_collision_chaining(void) {
    TEST("collision: bucket_count=1 forces all into one chain");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 1);
    for (int i = 0; i < 10; i++) {
        int val = i * 10;
        CHECK(hm_insert(hm, &i, &val) == DS_OK, "insert failed");
    }
    CHECK(hm->size == 10, "size wrong");
    for (int i = 0; i < 10; i++) {
        int out = -1;
        CHECK(hm_get(hm, &i, &out) == DS_OK, "get failed");
        CHECK(out == i * 10, "value wrong in chain");
    }
    hm_free(hm);
    PASS();
}

static void test_collision_remove_all_in_chain(void) {
    TEST("collision: remove all entries from single bucket");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 1);
    for (int i = 0; i < 5; i++) {
        int val = i;
        hm_insert(hm, &i, &val);
    }
    for (int i = 0; i < 5; i++)
        CHECK(hm_remove(hm, &i) == DS_OK, "remove from chain failed");
    CHECK(hm->size == 0, "size != 0");
    CHECK(hm->buckets[0] == NULL, "bucket not NULL after all removed");
    hm_free(hm);
    PASS();
}

/* ── 5. Edge / Stress ───────────────────── */

static void test_large_volume(void) {
    TEST("edge: 1000 entries inserted and verified");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 64);
    for (int i = 0; i < 1000; i++) {
        int val = i * 2;
        CHECK(hm_insert(hm, &i, &val) == DS_OK, "insert failed");
    }
    CHECK(hm->size == 1000, "size wrong");
    for (int i = 0; i < 1000; i++) {
        int out = -1;
        CHECK(hm_get(hm, &i, &out) == DS_OK, "get failed");
        CHECK(out == i * 2, "value wrong");
    }
    hm_free(hm);
    PASS();
}

static void test_insert_remove_interleaved(void) {
    TEST("edge: interleaved insert and remove");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int k1 = 1, k2 = 2, k3 = 3, val = 10;
    hm_insert(hm, &k1, &val); val = 20;
    hm_insert(hm, &k2, &val);
    hm_remove(hm, &k1);
    val = 30;
    hm_insert(hm, &k3, &val);
    hm_remove(hm, &k2);
    CHECK(hm->size == 1, "size wrong");
    int out = 0;
    CHECK(hm_get(hm, &k3, &out) == DS_OK && out == 30, "k3 wrong");
    CHECK(hm_get(hm, &k1, &out) == DS_ERR_NOT_FOUND, "k1 still present");
    CHECK(hm_get(hm, &k2, &out) == DS_ERR_NOT_FOUND, "k2 still present");
    hm_free(hm);
    PASS();
}

static void test_single_bucket_insert_get_remove(void) {
    TEST("edge: single entry insert, get, remove cycle");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 16);
    int key = 7, val = 77;
    hm_insert(hm, &key, &val);
    int out = 0;
    hm_get(hm, &key, &out);
    CHECK(out == 77, "get wrong");
    hm_remove(hm, &key);
    CHECK(hm->size == 0, "size wrong");
    CHECK(hm_get(hm, &key, &out) == DS_ERR_NOT_FOUND, "key still present");
    hm_free(hm);
    PASS();
}

static void test_point_key_person_value(void) {
    TEST("edge: Point key, Person value — full insert/get/remove");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(Point), sizeof(Person), 16);
    Point key = make_point(10, 20);
    Person val = make_person("Bob", 25);
    hm_insert(hm, &key, &val);
    Person out; memset(&out, 0, sizeof(out));
    CHECK(hm_get(hm, &key, &out) == DS_OK, "get failed");
    CHECK(strcmp(out.name, "Bob") == 0, "name wrong");
    CHECK(out.age == 25, "age wrong");
    CHECK(hm_remove(hm, &key) == DS_OK, "remove failed");
    CHECK(hm_get(hm, &key, &out) == DS_ERR_NOT_FOUND, "key still present");
    hm_free(hm);
    PASS();
}

static void test_free_with_collisions(void) {
    TEST("edge: free with multiple collisions doesn't leak");
    hashmap_s *hm = NULL;
    hm_init(&hm, sizeof(int), sizeof(int), 1);
    for (int i = 0; i < 20; i++) {
        int val = i;
        hm_insert(hm, &i, &val);
    }
    CHECK(hm_free(hm) == DS_OK, "free with collisions failed");
    PASS();
}

/* ═══════════════════════════════════════════
   MAIN
═══════════════════════════════════════════ */

int main(void) {
    printf("\n=== hashmap_s test suite ===\n\n");

    printf("[ Init / Free ]\n");
    test_init_basic();
    test_init_all_buckets_null();
    test_free_empty();

    printf("\n[ Insert / Get ]\n");
    test_insert_and_get_int();
    test_insert_and_get_multiple();
    test_insert_point_key();
    test_insert_person_value();
    test_insert_duplicate_key();
    test_get_missing_key();
    test_get_empty_bucket();

    printf("\n[ Remove ]\n");
    test_remove_basic();
    test_remove_missing_key();
    test_remove_empty_bucket();
    test_remove_head_of_chain();
    test_remove_middle_of_chain();
    test_remove_then_reinsert();

    printf("\n[ Collisions ]\n");
    test_collision_chaining();
    test_collision_remove_all_in_chain();

    printf("\n[ Edge / Stress ]\n");
    test_large_volume();
    test_insert_remove_interleaved();
    test_single_bucket_insert_get_remove();
    test_point_key_person_value();
    test_free_with_collisions();

    printf("\n═══════════════════════════════════════════\n");
    printf("Results: %d / %d passed\n\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}