#ifndef __ROPE_H
#define __ROPE_H

#include <stddef.h>

#include "rc.h"

#define KIND_LEAF   0x1A
#define KIND_BRANCH 0xA1

struct leaf {
	struct str_rc *rc;
	size_t sz;
	char *data;
};

struct branch {
    size_t weight;
    struct node *left;
    struct node *right;
};

struct node {
    int kind;
    union {
        struct leaf leaf;
        struct branch branch;
    };
};

struct rope {
    struct node head;
};

struct rope new_rope(char *s);
struct rope new_rope_dup(char *s);

#endif /* __ROPE_H */
