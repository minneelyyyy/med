#ifndef __RC_H
#define __RC_H

#include <stddef.h>

struct rc {
	void (*freefn)(void *);
	size_t rc;
	void *ptr;
};

/** make a reference counter from ptr
 * @param ptr a pointer to some data
 * @param freefn the function that should be called on ptr when rc reaches 0 */
struct rc rc_new(void *ptr, void (*freefn)(void *));
struct rc *rc_new_alloc(void *ptr, void (*freefn)(void *));

/** equivalent to rc_new(ptr, free) */
struct rc rc_new_f(void *ptr);
struct rc *rc_new_f_alloc(void *ptr);

/** free a rc regardless of its current reference count, very unsafe to call */
void rc_free(struct rc *rc);

/** clone a reference */
struct rc *rc_clone(struct rc *rc);

/** drop a reference */
void rc_forget(struct rc *rc);

#endif /* __RC_H */
