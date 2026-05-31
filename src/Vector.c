#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


vector_s *vector_init(size_t elem_size){
    vector_s *vector;
    if ((vector = calloc(1, sizeof(vector_s))) == NULL){
        fprintf(stderr, "Failed Vector Pointer...");
        return NULL;
    }

    vector->elem_size = elem_size;
    vector->size = 0;
    vector->capacity = 16;

    if ((vector->data = calloc(vector->capacity, vector->elem_size)) == NULL){
        fprintf(stderr, "Failed to Allocate Memory for Vector Data...");
        return NULL;
    }

    return vector;
}

vector_s *vector_push(vector_s *vector, void *element){
    if (vector->size >= vector->capacity){
        size_t new_capacity = vector->capacity * 1.5;
        void *tmp = realloc(vector->data, new_capacity * vector->elem_size);

        if (tmp == NULL){
            fprintf(stderr, "Failed to Reallocate Memory for Vector...");
            return NULL;
        }

        vector->data = tmp;
        vector->capacity = new_capacity;
    }
    
    char *base = (char *)vector->data;
    char *dest = base + vector->size * vector->elem_size;
    memcpy(dest, element, vector->elem_size);

    vector->size += 1;

    return vector;
}

void *vector_pop(vector_s *vector){
    if (vector->size == 0){
        fprintf(stderr, "This vector does not have any elements");
        return NULL;
    }
    vector->size -= 1;
    
    char *base = (char *)vector->data;
    char *element = base + vector->size * vector->elem_size;
    
    return (void *) element;
}

vector_s *vector_set(vector_s *vector, void *element, size_t index){
    if (index >= vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return NULL;
    }   

    char *base = (char *)vector->data;
    char *old_element = base + index * vector->elem_size;
    memcpy(old_element, element, vector->elem_size);

    return vector;
}

vector_s *vector_insert(vector_s *vector, void *element, size_t index){
    if (index > vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return NULL;
    }

    if (vector->size >= vector->capacity){
        size_t new_capacity = vector->capacity * 1.5;
        void *tmp = realloc(vector->data, new_capacity * vector->elem_size);

        if (tmp == NULL){
            fprintf(stderr, "Failed to Reallocate Memory for Vector...");
            return NULL;
        }
        
        vector->data = tmp;
        vector->capacity = new_capacity;
    }

    char *base = (char *)vector->data;
    char *index_element = base + index * vector->elem_size;

    // Moving all the items to the right.    
    size_t elements_to_copy = vector->size - index;
    memmove((index_element + vector->elem_size), index_element, elements_to_copy * vector->elem_size);

    // Copying the new element onto the index.
    memcpy(index_element, element, vector->elem_size);

    vector->size += 1;

    return vector;
}

void *vector_get(vector_s *vector, size_t index){
    if (index >= vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return NULL;
    }

    char *base = (char *)vector->data;
    char *element = base + index * vector->elem_size;

    return (void *) element;
}

vector_s *vector_remove(vector_s *vector, size_t index){
    if (index >= vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return NULL;
    }

    char *base = (char *)vector->data;
    char *index_element = base + index * vector->elem_size;
    size_t elements_to_copy = vector->size - index - 1;
    if (elements_to_copy > 0) {
        memmove(index_element,
                index_element + vector->elem_size,
                elements_to_copy * vector->elem_size);
    }
    vector->size -= 1;

    return vector;
}

void vector_free(vector_s *vector){
    if (vector == NULL){
        return;
    }

    if (vector->data != NULL){
        free(vector->data);
        vector->data;
    }

    free(vector);
    return;
}
