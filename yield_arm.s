#if defined(__arm__)

.text

.globl coro_yield
.align 4
coro_yield:
	ldr r2, [r0]
	str r4, [r0]
	mov r4, r2

	ldr r2, [r0, #4]
	str r5, [r0, #4]
	mov r5, r2

	ldr r2, [r0, #8]
	str r6, [r0, #8]
	mov r6, r2

	ldr r2, [r0, #12]
	str r7, [r0, #12]
	mov r7, r2

	ldr r2, [r0, #16]
	str r8, [r0, #16]
	mov r8, r2

	ldr r2, [r0, #20]
	str r9, [r0, #20]
	mov r9, r2

	ldr r2, [r0, #24]
	str r10, [r0, #24]
	mov r10, r2

	ldr r2, [r0, #28]
	str r11, [r0, #28]
	mov r11, r2

	ldr r2, [r0, #32]
	str r12, [r0, #32]
	mov r12, r2

	ldr r2, [r0, #36]
	str sp, [r0, #36]
	mov sp, r2

	ldr r2, [r0, #40]
	str lr, [r0, #40]
	mov lr, r2

	mov r0, r1
	
	bx lr

#endif
