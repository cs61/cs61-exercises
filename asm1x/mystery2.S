	.file	"mystery2.c"
	.text
	.globl	mystery2
	.type	mystery2, @function
mystery2:
.LFB0:
	movq	%rdi, %rax
	salq	$4, %rax
	addq	%rsi, %rax
	salq	$4, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	ret
.LFE0:
	.size	mystery2, .-mystery2
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
