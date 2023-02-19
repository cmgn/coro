#ifndef _CORO_H
#define _CORO_H

#include <stdint.h>

struct coro {
	uint64_t rbx;
	uint64_t rsp;
	uint64_t rbp;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
	uint64_t rip;
	void *stack;
	uint8_t done;
};

typedef void (*coro_func)(struct coro *, void *);

extern void *coro_yield(struct coro *c, void *);
extern void coro_init(struct coro *c, void *stack, uint64_t stacksz,
		      coro_func func, void *arg);
extern void coro_free(struct coro *c);
extern int coro_done(struct coro *c);
extern void *coro_resume(struct coro *c);

#endif
