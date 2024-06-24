#ifndef __BUFFER_H
#define __BUFFER_H

#include <stdio.h>
#include <sys/stat.h>

#include "rope.h"

struct buffer {
	struct stat st;
	FILE *file;
	char *file_data;
	struct rope rope;
};

#endif /* __BUFFER_H */
