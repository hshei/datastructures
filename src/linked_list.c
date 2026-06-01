#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    void       *data;
    struct node_s *next;
} node_s;

typedef struct {
    node_s *head;
    size_t  size;
    size_t  elem_size;
} linked_list_s;