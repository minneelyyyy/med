#define _XOPEN_SOURCE 500
#include "rc.h"

#include <stdlib.h>
#include <string.h>

#define sizeof_bits(x) (sizeof(x) * 8)

#define RC_COUNT(rc) ((rc)->rc & (~1 >> 1))
#define RC_MAKE_HEAP_ALLOCATED(sz) ((sz) | ((typeof(sz)) 1 << (sizeof_bits(sz) - 1)))
#define RC_IS_HEAP_ALLOCATED(rc) (!!((rc)->rc & (sizeof_bits((rc)->rc) - 1)))

struct rc rc_new(void *ptr, void (*freefn)(void *)) {
	struct rc rc;

	rc.rc = 1;
	rc.freefn = freefn;
	rc.ptr = ptr;

	return rc;
}

struct rc *rc_new_alloc(void *ptr, void (*freefn)(void *)) {
	struct rc *rc = malloc(sizeof *rc);

	*rc = rc_new(ptr, freefn);
	rc->rc = RC_MAKE_HEAP_ALLOCATED(RC_COUNT(rc));

	return rc;
}

struct rc rc_new_f(void *ptr) {
	return rc_new(ptr, free);
}

struct rc *rc_new_f_alloc(void *ptr) {
	return rc_new_alloc(ptr, free);
}

void rc_free(struct rc *rc) {
	rc->freefn(rc->ptr);

	if (RC_IS_HEAP_ALLOCATED(rc)) {
		free(rc);
		return;
	}

	rc->ptr = NULL; /* we set the pointer to NULL,
			 * so that an access post free will crash. */
}

/* simply increasing and decreasing rc is fine,
 * since the top bit won't be altered in normal situations.
 * only if the reference count goes above 2^63 or below 0, which it never will */

struct rc *rc_clone(struct rc *rc) {
	rc->rc++;
	return rc;
}

void rc_forget(struct rc *rc) {
	rc->rc--;

	if (RC_COUNT(rc) == 0)
		rc_free(rc);
}
