#define _XOPEN_SOURCE 500

#include "rope.h"

#include <stdlib.h>
#include <string.h>

struct rope new_rope(char *s) {
	struct rope r;

	r.head.kind = KIND_LEAF;
	*r.head.leaf.rc = strrc_new_own(s);
	r.head.leaf.sz = strlen(r.head.leaf.rc->str);
	r.head.leaf.data = r.head.leaf.rc->str;

	return r;
}

struct rope new_rope_dup(char *s) {
	return new_rope(strdup(s));
}

