#include <stdio.h>
#include <stdlib.h>

#include "coro.h"

#define STACK_SIZE (64 * 1024)

struct t {
	struct t *left;
	struct t *right;
	int val;
};

void insert(struct t **root, struct t *new)
{
	struct t **curr = root;
	while (*curr) {
		if (new->val < (*curr)->val) { curr = &(*curr)->left;
		} else {
			curr = &(*curr)->right;
		}
	}
	*curr = new;
}

void iterator(struct coro *c, struct t *t)
{
	if (t) {
		iterator(c, t->left);
		coro_yield(c, (void *)t->val);
		iterator(c, t->right);
	}
}

int main()
{
	struct t *root = 0;
	int vals[] = { 4, 2, 1, 3, 6, 5, 7 };
	struct t nodes[sizeof(vals) / sizeof(*vals)] = { 0 };
	for (int i = 0; i < sizeof(vals) / sizeof(*vals); i++) {
		nodes[i].val = vals[i];
		insert(&root, &nodes[i]);
	}
	struct coro c = { 0 };
	void *stack = calloc(1, STACK_SIZE);
	if (!stack) {
		perror("calloc");
		return 1;
	}
	coro_init(&c, stack, STACK_SIZE, (coro_func)iterator, root);
	int n = (int)coro_resume(&c);
	while (!coro_done(&c)) {
		printf("%d\n", n);
		n = (int)coro_resume(&c);
	}
	coro_free(&c);
	return 0;
}
