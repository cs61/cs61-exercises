	.file	"mystery2.c"
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
.LFB23:
	testq	%rdi, %rdi
	je	.L5
	cmpl	%esi, (%rdi)
	jne	.L3
	jmp	.L6
.L4:
	cmpl	%esi, (%rdi)
	je	.L7
.L3:
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
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
.LFE23:
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
