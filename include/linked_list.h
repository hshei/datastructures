#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct node_s {
    void       *data;
    struct node_s *next;
} node_s;

typedef struct {
    node_s *head;
    node_s *tail;
    size_t  size;
    size_t  elem_size;
} linked_list_s;

// Linked list function declarations
ds_err_t llist_init(linked_list_s **llist_out, size_t elem_size);
ds_err_t llist_push_front(linked_list_s *llist, void *element);
ds_err_t llist_push_back(linked_list_s *llist, void *element);
ds_err_t llist_pop_front(linked_list_s *llist, void *element_out);
ds_err_t llist_pop_back(linked_list_s *llist, void *element_out);
ds_err_t llist_get(linked_list_s *llist, size_t index, void *element_out);
ds_err_t llist_set(linked_list_s *llist, void *element, size_t index);
ds_err_t llist_insert(linked_list_s *llist, void *element, size_t index);
ds_err_t llist_remove(linked_list_s *llist, size_t index);
ds_err_t llist_free(linked_list_s *llist);