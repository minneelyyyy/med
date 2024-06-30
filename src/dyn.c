#include "dyn.h"

#include <stdlib.h>

struct array array_new_cap(size_t icap) {
    struct array arr;

    arr.cap = icap;
    arr.size = 0;
    arr.elems = malloc(sizeof(*arr.elems) * arr.cap);

    return arr;
}

struct array array_new(void) {
    return array_new_cap(8);
}

void array_free(struct array *arr) {
    free(arr->elems);
}

struct array *array_push(struct array *arr, void *ptr) {
    if (arr->size == arr->cap) {
        size_t new_cap = arr->cap * 3 / 2;
        void **newelems = realloc(arr->elems, sizeof(*arr->elems) * new_cap);

        if (!newelems) return NULL;
    }

    arr->elems[arr->size++] = ptr;

    return arr;
}

void *array_pop(struct array *arr) {
    return arr->elems[arr->size--];
}
