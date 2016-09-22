	.file	"mystery1.c"
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
.LFB0:
	leaq	4(%rdi), %r8
	movl	(%rdi), %edx
	subl	$1, %edx
	js	.L7
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edi
	cltq
	movl	(%r8,%rax,4), %eax
	cmpl	%esi, %eax
	je	.L8
	movl	$0, %ecx
	jmp	.L3
.L6:
	leal	(%rcx,%rdx), %eax
	movl	%eax, %edi
	shrl	$31, %edi
	addl	%edi, %eax
	sarl	%eax
	movl	%eax, %edi
	cltq
	movl	(%r8,%rax,4), %eax
	cmpl	%esi, %eax
	je	.L9
.L3:
	cmpl	%eax, %esi
	jle	.L4
	leal	1(%rdi), %ecx
	jmp	.L5
.L4:
	leal	-1(%rdi), %edx
.L5:
	cmpl	%edx, %ecx
	jle	.L6
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
.LFE0:
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
