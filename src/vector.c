#include "vector.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ds_err_t vector_init(vector_s **vector_out, size_t elem_size){
    vector_s *vector;
    if ((vector = calloc(1, sizeof(vector_s))) == NULL){  
        fprintf(stderr, "Failed to Allocate Memory for Vector Data...");
        return DS_ERR_ALLOC;
    }

    vector->elem_size = elem_size;
    vector->size = 0;
    vector->capacity = 16;

    if ((vector->data = calloc(vector->capacity, vector->elem_size)) == NULL){
        fprintf(stderr, "Failed to Allocate Memory for Vector Data...");
        free(vector); 
        return DS_ERR_ALLOC;
    }

    *vector_out = vector;
    return DS_OK;
}

size_t vector_size(const vector_s *vector){
    return vector->size;
}

size_t vector_capacity(const vector_s *vector){
    return vector->capacity;
}

ds_err_t vector_push(vector_s *vector, void *element){
    if (vector->size >= vector->capacity){
        size_t new_capacity = vector->capacity + (vector->capacity / 2); 
        void *tmp = realloc(vector->data, new_capacity * vector->elem_size);

        if (tmp == NULL){
            fprintf(stderr, "Failed to Reallocate Memory for Vector...");
            return DS_ERR_ALLOC;
        }

        vector->data = tmp;
        vector->capacity = new_capacity;
    }
    
    char *base = (char *)vector->data;
    char *dest = base + vector->size * vector->elem_size;
    memcpy(dest, element, vector->elem_size);

    vector->size += 1;

    return DS_OK;
}

ds_err_t vector_pop(vector_s *vector, void *element_out){
    if (vector->size == 0){
        fprintf(stderr, "This vector does not have any elements");
        return DS_ERR_EMPTY;
    }
    vector->size -= 1;
    
    char *base = (char *)vector->data;
    char *element = base + vector->size * vector->elem_size;
    
    memcpy(element_out, element, vector->elem_size);    
    return DS_OK;
}

ds_err_t vector_set(vector_s *vector, void *element, size_t index){
    if (index >= vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return DS_ERR_OUT_OF_BOUNDS;
    }   

    char *base = (char *)vector->data;
    char *old_element = base + index * vector->elem_size;
    memcpy(old_element, element, vector->elem_size);

    return DS_OK;
}

ds_err_t vector_insert(vector_s *vector, void *element, size_t index){
    if (index > vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return DS_ERR_OUT_OF_BOUNDS;
    }

    if (vector->size >= vector->capacity){
        size_t new_capacity = vector->capacity + (vector->capacity / 2);
        void *tmp = realloc(vector->data, new_capacity * vector->elem_size);

        if (tmp == NULL){
            fprintf(stderr, "Failed to Reallocate Memory for Vector...");
            return DS_ERR_ALLOC;
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

    return DS_OK;
}

ds_err_t vector_get(vector_s *vector, size_t index, void *element_out){
    if (index >= vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return DS_ERR_OUT_OF_BOUNDS;
    }

    char *base = (char *)vector->data;
    char *element = base + index * vector->elem_size;

    memcpy(element_out, element, vector->elem_size);
    return DS_OK;
}

ds_err_t vector_remove(vector_s *vector, size_t index){
    if (index >= vector->size){
        fprintf(stderr, "Invalid Index, the current size of the vector is %zu\n", vector->size);
        return DS_ERR_OUT_OF_BOUNDS;
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

    return DS_OK;
}

ds_err_t vector_free(vector_s *vector){
    if (vector == NULL){
        return DS_OK;
    }

    if (vector->data != NULL){
        free(vector->data);
        vector->data = NULL;
    }

    free(vector);
    return DS_OK;
}
