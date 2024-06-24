#ifndef __RC_H
#define __RC_H

#include <stddef.h>

struct str_rc {
	size_t rc;
	char *str;
};

struct str_rc strrc_new(char *s);
struct str_rc strrc_new_own(char *s);
void strrc_free(struct str_rc *s);

struct str_rc *strrc_clone(struct str_rc *s);
void strrc_forget(struct str_rc *s);

#endif /* __RC_H */
