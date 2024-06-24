#define _XOPEN_SOURCE 500
#include "rc.h"

#include <stdlib.h>
#include <string.h>

struct str_rc strrc_new(char *s) {
	return strrc_new_own(strdup(s));
}

struct str_rc strrc_new_own(char *s) {
	struct str_rc rc;

	rc.rc = 1;
	rc.str = s;

	return rc;
}

void strrc_free(struct str_rc *s) {
	free(s->str);
}

struct str_rc *strrc_clone(struct str_rc *s) {
	s->rc++;
	return s;
}

void strrc_forget(struct str_rc *s) {
	s->rc--;

	if (s->rc == 0)
		strrc_free(s);
}
