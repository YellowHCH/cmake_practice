	.text
	.file	"restrict.cc"
	.globl	_Z21func_without_restrictPiS_S_ # -- Begin function _Z21func_without_restrictPiS_S_
	.p2align	4, 0x90
	.type	_Z21func_without_restrictPiS_S_,@function
_Z21func_without_restrictPiS_S_:        # @_Z21func_without_restrictPiS_S_
	.cfi_startproc
# %bb.0:
	movl	(%rdx), %eax
	addl	%eax, (%rdi)
	movl	(%rsi), %eax
	imull	(%rdx), %eax
	movl	%eax, (%rsi)
	retq
.Lfunc_end0:
	.size	_Z21func_without_restrictPiS_S_, .Lfunc_end0-_Z21func_without_restrictPiS_S_
	.cfi_endproc
                                        # -- End function
	.globl	_Z18func_with_restrictPiS_S_    # -- Begin function _Z18func_with_restrictPiS_S_
	.p2align	4, 0x90
	.type	_Z18func_with_restrictPiS_S_,@function
_Z18func_with_restrictPiS_S_:           # @_Z18func_with_restrictPiS_S_
	.cfi_startproc
# %bb.0:
	movl	(%rdx), %eax
	addl	%eax, (%rdi)
	imull	(%rsi), %eax
	movl	%eax, (%rsi)
	retq
.Lfunc_end1:
	.size	_Z18func_with_restrictPiS_S_, .Lfunc_end1-_Z18func_with_restrictPiS_S_
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$.L.str, %edi
	movl	$1, %esi
	movl	$2, %edx
	movl	$3, %ecx
	xorl	%eax, %eax
	callq	printf
	movl	$.L.str.1, %edi
	movl	$7, %esi
	movl	$18, %edx
	movl	$3, %ecx
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Before: a=%d, b=%d, c=%d\n"
	.size	.L.str, 26

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"After: a=%d, b=%d, c=%d\n"
	.size	.L.str.1, 25

	.ident	"Debian clang version 11.0.1-2"
	.section	".note.GNU-stack","",@progbits
	.addrsig
