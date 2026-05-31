#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vector_s {
    void *data;
    size_t size;
    size_t capacity;
    size_t elem_size;
} vector_s;

vector_s *vector_init(size_t elem_size);
vector_s *vector_push(vector_s *vector, void *element);
void *vector_pop(vector_s *vector);
vector_s *vector_set(vector_s *vector, void *element, size_t index);
vector_s *vector_insert(vector_s *vector, void *element, size_t index);
void *vector_get(vector_s *vector, size_t index);
vector_s *vector_remove(vector_s *vector, size_t index);
void *vector_free(vector_s *vector);

#endif // VECTOR_H
