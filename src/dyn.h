#ifndef __DYN_H
#define __DYN_H

#include <stddef.h>

struct array {
    size_t cap, size;
    void **elems;
};

struct array array_new(void);
struct array array_new_cap(size_t icap);
void array_free(struct array* arr);

struct array *array_push(struct array *arr, void *ptr);
void *array_pop(struct array *arr);

static inline size_t array_cap(const struct array *arr) { return arr->cap; }
static inline size_t array_size(const struct array *arr) { return arr->size; }

#endif /* __DYN_H */