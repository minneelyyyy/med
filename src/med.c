#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>

#include <unistd.h>

#include <ncurses.h>

#include "buffer.h"

struct options {};

int help(int exit_status) {
	fprintf(stderr, "USAGE: med [FILE...]\n");
	exit(exit_status);
}

int med(const struct options *opts, char **files, int filecnt) {
	struct buffer *buffers;
	int i;

	buffers = malloc(filecnt * sizeof(*buffers));

	for (i = 0; i < filecnt; i++) {
		/* TODO: initialize buffers[i] */
	}

	initscr();
	cbreak();
	noecho();

	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	for (;;) {
		refresh();
	}

	endwin();

	for (i = 0; i < filecnt; i++) {
		/*TODO: free buffers[i] */
	}

	free(buffers);

	return 0;
}

int main(int argc, char **argv) {
	int c;
	
	setlocale(LC_ALL, "");

	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
			case '?': case 'h':
				help(0);
		}
	}

	return med(NULL, &argv[optind], argc - optind);
}
