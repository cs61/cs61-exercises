	.file	"mystery1.c"
	.text
	.globl	mystery1
	.type	mystery1, @function
mystery1:
.LFB0:
	imull	$300, %edi, %eax
	imull	$500, %esi, %esi
	addl	%esi, %eax
	addl	%edx, %eax
	ret
.LFE0:
	.size	mystery1, .-mystery1
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
