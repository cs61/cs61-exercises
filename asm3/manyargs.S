# This is manyargs compiled with -O1
	.file	"manyargs.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"A1 = %d\n"
.LC1:
	.string	"A2 = %ld\n"
.LC2:
	.string	"A3 = %c\n"
.LC3:
	.string	"A4 = %hd\n"
.LC4:
	.string	"A5 = %x\n"
.LC5:
	.string	"A6 = %lx\n"
.LC6:
	.string	"A7 = %cx\n"
.LC7:
	.string	"A8 = %hx\n"
	.text
	.globl	manyargs
	.type	manyargs, @function
manyargs:
.LFB23:
	pushq	%r15			# Save callee saved registers
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbp
	pushq	%rbx			# 6 of them = 48 bytes
	subq	$24, %rsp		# Create stack frame
	movq	%rsi, %r15		# r15 = a2
	movl	%edx, %r14d		# r14d = a3
	movl	%ecx, %r13d		# r13d = a4
	movl	%r8d, %r12d		# r12d = a5
	movq	%r9, %rbp		# rbp = a6
	movl	80(%rsp), %ebx		# ebx = a7
	movl	88(%rsp), %eax		# eax = a8
	movl	%eax, 12(%rsp)		# Store eax in local
	movl	%edi, %edx		# a1 becomes 3rd arg to print
	movl	$.LC0, %esi		# Print first argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movq	%r15, %rdx
	movl	$.LC1, %esi		# Print second argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movsbl	%r14b, %edx
	movl	$.LC2, %esi		# Print third argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movswl	%r13w, %edx
	movl	$.LC3, %esi		# Print fourth argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	%r12d, %edx
	movl	$.LC4, %esi		# Print fifth argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movq	%rbp, %rdx
	movl	$.LC5, %esi		# Print sixth argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movzbl	%bl, %edx
	movl	$.LC6, %esi		# Print seventh argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movzwl	12(%rsp), %edx
	movl	$.LC7, %esi		# Print eighth argument
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
.LFE23:
	.size	manyargs, .-manyargs
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
