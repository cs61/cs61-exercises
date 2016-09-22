	.file	"mystery4.c"
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
.LFB0:
	leaq	4(%rdi), %rdx
	movl	(%rdi), %eax
	testl	%eax, %eax
	jle	.L5
	cmpl	%esi, 4(%rdi)
	je	.L6
	addq	$8, %rdi
	leal	-1(%rax), %eax
	leaq	4(%rdx,%rax,4), %rax
	jmp	.L3
.L4:
	addq	$4, %rdi
	cmpl	%esi, -4(%rdi)
	je	.L7
.L3:
	cmpq	%rax, %rdi
	jne	.L4
	movl	$0, %eax
	ret
.L5:
	movl	$0, %eax
	ret
.L6:
	movl	$1, %eax
	ret
.L7:
	movl	$1, %eax
	ret
.LFE0:
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
