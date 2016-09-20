	.file	"mystery4.c"
	.text
	.globl	mystery4
	.type	mystery4, @function
mystery4:
.LFB0:
	pushq	%rbx
	movl	%edi, %ebx
	movl	$0, %eax
	testl	%edi, %edi
	je	.L2
	leal	-1(%rdi), %edi
	call	mystery4
	addl	%ebx, %eax
.L2:
	popq	%rbx
	ret
.LFE0:
	.size	mystery4, .-mystery4
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
