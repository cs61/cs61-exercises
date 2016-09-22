	.file	"2a.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	<Format String removed>
	.text
	.globl	output_func
	.type	output_func, @function
output_func:
.LFB23:
	subq	$8, %rsp
	movslq	%esi, %rsi
	movl	(%rdi,%rsi,4), %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	addq	$8, %rsp
	ret
.LFE23:
	.size	output_func, .-output_func
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
