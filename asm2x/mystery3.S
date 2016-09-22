	.file	"mystery3.c"
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
.LFB23:
	testq	%rdi, %rdi
	je	.L7
	movl	(%rdi), %eax
	cmpl	%esi, %eax
	jne	.L3
	jmp	.L8
.L6:
	movl	(%rdi), %eax
	cmpl	%esi, %eax
	je	.L9
.L3:
	cmpl	%eax, %esi
	jle	.L4
	movq	16(%rdi), %rdi
	jmp	.L5
.L4:
	movq	8(%rdi), %rdi
.L5:
	testq	%rdi, %rdi
	jne	.L6
	movl	$0, %eax
	ret
.L7:
	movl	$0, %eax
	ret
.L8:
	movl	$1, %eax
	ret
.L9:
	movl	$1, %eax
	ret
.LFE23:
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
