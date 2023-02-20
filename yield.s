.text

.global coro_yield

coro_yield:
	movq 0(%rdi), %r8
	movq %rbx, 0(%rdi)
	movq %r8, %rbx

	movq 8(%rdi), %r8
	movq %rsp, 8(%rdi)
	movq %r8, %rsp

	movq 16(%rdi), %r8
	movq %rbp, 16(%rdi)
	movq %r8, %rbp

	movq 24(%rdi), %r8
	movq %r12, 24(%rdi)
	movq %r8, %r12

	movq 32(%rdi), %r8
	movq %r13, 32(%rdi)
	movq %r8, %r13

	movq 40(%rdi), %r8
	movq %r14, 40(%rdi)
	movq %r8, %r14

	movq 48(%rdi), %r8
	movq %r15, 48(%rdi)
	movq %r8, %r15

	movq %rsi, %rax

	ret
