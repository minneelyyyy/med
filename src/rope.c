#define _XOPEN_SOURCE 500

#include "rope.h"
#include "fib.h"

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

struct rope rope_new_dup(const char *s) {
	return rope_new(strdup(s));
}

/* TODO: implement freeing of entire tree */
void rope_free(struct rope *rope) {
	fprintf(stderr, "WARNING: rope_free(%p) called, however it is unimplemented! There is a memory leak.\n", rope);
}

static struct node *node_left(struct node *n) {
	return n->kind == KIND_BRANCH
		? n->branch.left
		: NULL;
}

static struct node *node_right(struct node *n) {
	return n->kind == KIND_BRANCH
		? n->branch.right
		: NULL;
}

static struct node *node_collect_iter_next(struct array *temp) {
	struct node *n = array_pop(temp);

	if (temp->size > 0) {
		struct node *parent = array_pop(temp);
		struct node *right = node_right(parent);

		if (right != NULL) {
			array_push(temp, right);
			struct node *left = node_left(right);

			while (left != NULL) {
				array_push(temp, left);
				left = node_left(left);
			}
		}
	}

	return n;
}

static struct array node_collect(struct node *n) {
	struct array nodes = array_new();
	struct array temp = array_new();
	struct node *node = n;

	while (node) {
		array_push(&temp, node);
		node = node_left(node);
	}

	while (node = node_collect_iter_next(&temp))
		array_push(&nodes, node);

	array_free(&temp);

	return nodes;
}

struct array rope_collect(struct rope *r) {
	return node_collect(&r->head);
}
