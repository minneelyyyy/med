#define _XOPEN_SOURCE 500

#include "rope.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rope rope_new(char *s) {
	struct rope r;

	r.head.kind = KIND_LEAF;
	r.head.leaf.data = s;
	r.head.leaf.sz = strlen(s);
	r.head.leaf.rc = rc_new_f_alloc(s);

	return r;
}

struct rope rope_new_dup(char *s) {
	return rope_new(strdup(s));
}

/* TODO: implement freeing of entire tree */
void rope_free(struct rope *rope) {
	fprintf(stderr, "WARNING: rope_free(%p) called, however it is unimplemented! There is a memory leak.\n", rope);
}
