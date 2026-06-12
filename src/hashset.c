#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashset.h"
#include "error.h"

// djb2
static size_t hash(const void *key, size_t key_size, size_t bucket_count){
    const unsigned char *bytes = (const unsigned char *)key;
    size_t h = 5381;
    for (size_t i = 0; i < key_size; i++)
        h = h * 33 + bytes[i];
    return h % bucket_count;
}


static ds_err_t hs_rehash(hashset_s *hs){
    size_t new_count = hs->bucket_count * 2;
    hs_entry_s **new_bucket;
    if ((new_bucket = calloc(new_count, sizeof(hs_entry_s *))) == NULL) return DS_ERR_ALLOC;
    for (size_t i = 0; i < hs->bucket_count; i++){
        hs_entry_s *entry = hs->buckets[i];
        if (entry == NULL) continue;
        while (entry != NULL){
            hs_entry_s *next_entry = entry->next;
            size_t new_index = hash(entry->key, hs->key_size, new_count);
            entry->next = new_bucket[new_index];
            new_bucket[new_index] = entry;
            entry = next_entry;
        }
    }
    free(hs->buckets);
    hs->buckets = new_bucket;
    hs->bucket_count = new_count;

    return DS_OK;
}

ds_err_t hs_init(hashset_s **hs_out, size_t key_size, size_t bucket_count){
    hashset_s *hs;
    if ((hs = calloc(1, sizeof(hashset_s))) == NULL) return DS_ERR_ALLOC;
    if ((hs->buckets = calloc(bucket_count, sizeof(hs_entry_s * ))) == NULL){
        free(hs);
        return DS_ERR_ALLOC;
    }

    hs->bucket_count = bucket_count;
    hs->size = 0;
    hs->key_size = key_size;

    *hs_out = hs;
    return DS_OK;
}

ds_err_t hs_insert(hashset_s *hs, void *key){
    size_t index = hash(key, hs->key_size, hs->bucket_count);

    for (hs_entry_s *temp = hs->buckets[index]; temp != NULL; temp = temp->next){
        // if the entry already exists, nothing to add
        if (memcmp(key, temp->key, hs->key_size) == 0) return DS_OK;
    }

    // if the entry doesn't exist, add at the head
    hs_entry_s *new_entry;
    if ((new_entry = calloc(1, sizeof(hs_entry_s))) == NULL) return DS_ERR_ALLOC;
    if ((new_entry->key = calloc(1, hs->key_size)) == NULL){
        free(new_entry);
        return DS_ERR_ALLOC;
    }

    memcpy(new_entry->key, key, hs->key_size);
    new_entry->next = hs->buckets[index];
    hs->buckets[index] = new_entry;

    hs->size += 1;

    if ((double)hs->size / (double)hs->bucket_count > 0.75)
        return hs_rehash(hs);

    return DS_OK;
}

ds_err_t hs_contains(hashset_s *hs, void *key, int *result){
    size_t index = hash(key, hs->key_size, hs->bucket_count);
    for (hs_entry_s *temp = hs->buckets[index]; temp != NULL; temp = temp->next){
        if (memcmp(temp->key, key, hs->key_size) == 0) {
            *result = 1;
            return DS_OK;
        }
    }
    *result = 0;
    return DS_OK;
}


ds_err_t hs_remove(hashset_s *hs, void *key){
    size_t index = hash(key, hs->key_size, hs->bucket_count);

    hs_entry_s *entry;
    hs_entry_s *prev_entry = NULL;
    // If bucket is empty
    if (hs->buckets[index] == NULL) return DS_ERR_NOT_FOUND;
    // Entry at the head)
    for (entry=hs->buckets[index]; entry!=NULL; entry=entry->next){
        if (memcmp(entry->key, key, hs->key_size) == 0){
            if (prev_entry == NULL) hs->buckets[index]=entry->next;
            else prev_entry->next = entry->next;
            free(entry->key);
            free(entry);
            hs->size -= 1;
            return DS_OK;
        }
        else prev_entry = entry;
    }
    return DS_ERR_NOT_FOUND;
}

ds_err_t hs_free(hashset_s *hs){
    if (hs == NULL) return DS_OK;

    hs_entry_s *entry, *next_entry;
    for (size_t i =0; i < hs->bucket_count; i++){
        entry=hs->buckets[i];
        if (entry == NULL) continue;
        while (entry != NULL){
            next_entry = entry->next;
            free(entry->key);
            free(entry);
            entry = next_entry;
        }
    }
    
    free(hs->buckets);
    free(hs);
    return DS_OK;
}