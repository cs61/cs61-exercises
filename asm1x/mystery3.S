	.file	"mystery3.c"
	.text
	.globl	op1
	.type	op1, @function
op1:
.LFB23:
	movl	%edi, %eax
	andl	%esi, %eax
	notl	%eax
	ret
.LFE23:
	.size	op1, .-op1
	.globl	op2
	.type	op2, @function
op2:
.LFB24:
	notl	%edi
	movl	%edi, %eax
	orl	%esi, %eax
	ret
.LFE24:
	.size	op2, .-op2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"It worked!"
	.text
	.globl	mystery3
	.type	mystery3, @function
mystery3:
.LFB25:
	movl	%edi, %eax
	andl	%esi, %eax
	notl	%eax
	notl	%edi
	orl	%edi, %esi
	cmpl	%esi, %eax
	jne	.L7
	subq	$8, %rsp
	movl	$.LC0, %edi
	call	puts
	addq	$8, %rsp
.L7:
	rep ret
.LFE25:
	.size	mystery3, .-mystery3
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
