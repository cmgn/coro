#ifndef _CORO_H
#define _CORO_H

#include <stdint.h>

struct coro {
#if defined(__x86_64__)
	uint64_t rbx;
	uint64_t rsp;
	uint64_t rbp;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
#elif defined(__arm__)
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
	uint32_t sp;
	uint32_t lr;
#else
#error "unknown architecture"
#endif
	void *stack;
	uint8_t done;
};

typedef void (*coro_func)(struct coro *, void *);

extern void *coro_yield(struct coro *c, void *);
extern void coro_init(struct coro *c, void *stack, uint32_t stacksz,
		      coro_func func, void *arg);
extern void coro_free(struct coro *c);
extern int coro_done(struct coro *c);
extern void *coro_resume(struct coro *c);

#endif
