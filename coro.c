#include <stdlib.h>

#include "coro.h"

void coro_entrypoint(struct coro *c)
{
	coro_func f = (coro_func)coro_yield(c, 0);
	void *arg = coro_yield(c, 0);
	coro_yield(c, 0);
	f(c, arg);
	c->done = 1;
	coro_yield(c, 0);
}

void coro_init(struct coro *c, void *stack, uint64_t stacksz, coro_func func,
	       void *arg)
{
	c->stack = (void *)stack;
	c->rbp = c->rbp;
	*(uint64_t *)(stack + stacksz - 8) = (uint64_t)coro_entrypoint;
	c->rsp = (uint64_t)stack + stacksz - 8;
	coro_yield(c, 0);
	coro_yield(c, func);
	coro_yield(c, arg);
}

void coro_free(struct coro *c)
{
	free(c->stack);
}

int coro_done(struct coro *c)
{
	return c->done;
}

void *coro_resume(struct coro *c)
{
	return coro_yield(c, 0);
}
