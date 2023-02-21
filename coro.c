#include <stdlib.h>

#include "coro.h"

void coro_entrypoint(struct coro *c)
{
	coro_func f = coro_yield(c, 0);
	void *arg = coro_yield(c, 0);
	coro_yield(c, 0);
	f(c, arg);
	c->done = 1;
	coro_yield(c, 0);
}

void coro_init(struct coro *c, void *stack, uint32_t stacksz, coro_func func,
	       void *arg)
{
	c->stack = (void *)stack;
#if defined(__x86_64__)
	*(uint64_t *)(stack + stacksz - 8) = (uint64_t)coro_entrypoint;
	c->rsp = (uint64_t)stack + stacksz - 8;
#elif defined(__arm__)
	c->sp = (uint32_t)stack + stacksz;
	c->lr = (uint32_t)coro_entrypoint;
#else
#error "unknown architecture"
#endif
	coro_yield(c, c);
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
