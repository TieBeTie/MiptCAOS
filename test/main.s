	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	merge
	.type	merge, @function
merge:
.LFB5:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 52
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -44[ebp], eax
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	mov	eax, esp
	mov	ebx, eax
	mov	eax, DWORD PTR 16[ebp]
	sub	eax, DWORD PTR 12[ebp]
	mov	edx, eax
	shr	edx, 31
	add	eax, edx
	sar	eax
	mov	edx, eax
	mov	eax, DWORD PTR 12[ebp]
	add	eax, edx
	mov	DWORD PTR -24[ebp], eax
	mov	DWORD PTR -28[ebp], 0
	mov	DWORD PTR -32[ebp], 0
	mov	eax, DWORD PTR 16[ebp]
	sub	eax, DWORD PTR 12[ebp]
	lea	edx, -1[eax]
	mov	DWORD PTR -20[ebp], edx
	sal	eax, 2
	lea	edx, 3[eax]
	mov	eax, 16
	sub	eax, 1
	add	eax, edx
	mov	ecx, 16
	mov	edx, 0
	div	ecx
	imul	eax, eax, 16
	sub	esp, eax
	mov	eax, esp
	add	eax, 3
	shr	eax, 2
	sal	eax, 2
	mov	DWORD PTR -16[ebp], eax
	jmp	.L2
.L5:
	mov	edx, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR -28[ebp]
	add	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	add	eax, edx
	mov	edx, DWORD PTR [eax]
	mov	ecx, DWORD PTR -24[ebp]
	mov	eax, DWORD PTR -32[ebp]
	add	eax, ecx
	lea	ecx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	add	eax, ecx
	mov	eax, DWORD PTR [eax]
	cmp	edx, eax
	jge	.L3
	mov	edx, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR -28[ebp]
	add	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	add	eax, edx
	mov	ecx, DWORD PTR -28[ebp]
	mov	edx, DWORD PTR -32[ebp]
	add	ecx, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	DWORD PTR [eax+ecx*4], edx
	add	DWORD PTR -28[ebp], 1
	jmp	.L2
.L3:
	mov	edx, DWORD PTR -24[ebp]
	mov	eax, DWORD PTR -32[ebp]
	add	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	add	eax, edx
	mov	ecx, DWORD PTR -28[ebp]
	mov	edx, DWORD PTR -32[ebp]
	add	ecx, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	DWORD PTR [eax+ecx*4], edx
	add	DWORD PTR -32[ebp], 1
.L2:
	mov	edx, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR -28[ebp]
	add	eax, edx
	cmp	DWORD PTR -24[ebp], eax
	jle	.L6
	mov	edx, DWORD PTR -24[ebp]
	mov	eax, DWORD PTR -32[ebp]
	add	eax, edx
	cmp	DWORD PTR 16[ebp], eax
	jg	.L5
	jmp	.L6
.L7:
	mov	edx, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR -28[ebp]
	add	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	add	eax, edx
	mov	ecx, DWORD PTR -28[ebp]
	mov	edx, DWORD PTR -32[ebp]
	add	ecx, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	DWORD PTR [eax+ecx*4], edx
	add	DWORD PTR -28[ebp], 1
.L6:
	mov	edx, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR -28[ebp]
	add	eax, edx
	cmp	DWORD PTR -24[ebp], eax
	jg	.L7
	jmp	.L8
.L9:
	mov	edx, DWORD PTR -24[ebp]
	mov	eax, DWORD PTR -32[ebp]
	add	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	add	eax, edx
	mov	ecx, DWORD PTR -28[ebp]
	mov	edx, DWORD PTR -32[ebp]
	add	ecx, edx
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	DWORD PTR [eax+ecx*4], edx
	add	DWORD PTR -32[ebp], 1
.L8:
	mov	edx, DWORD PTR -24[ebp]
	mov	eax, DWORD PTR -32[ebp]
	add	eax, edx
	cmp	DWORD PTR 16[ebp], eax
	jg	.L9
	mov	DWORD PTR -36[ebp], 0
	jmp	.L10
.L11:
	mov	edx, DWORD PTR 12[ebp]
	mov	eax, DWORD PTR -36[ebp]
	add	eax, edx
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -44[ebp]
	lea	ecx, [edx+eax]
	mov	eax, DWORD PTR -16[ebp]
	mov	edx, DWORD PTR -36[ebp]
	mov	eax, DWORD PTR [eax+edx*4]
	mov	DWORD PTR [ecx], eax
	add	DWORD PTR -36[ebp], 1
.L10:
	mov	eax, DWORD PTR 16[ebp]
	sub	eax, DWORD PTR 12[ebp]
	cmp	DWORD PTR -36[ebp], eax
	jl	.L11
	mov	esp, ebx
	nop
	mov	eax, DWORD PTR -12[ebp]
	xor	eax, DWORD PTR gs:20
	je	.L12
	call	__stack_chk_fail_local
.L12:
	mov	ebx, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	merge, .-merge
	.globl	mergeSort
	.type	mergeSort, @function
mergeSort:
.LFB6:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 12[ebp]
	add	eax, 1
	cmp	DWORD PTR 16[ebp], eax
	jle	.L16
	mov	eax, DWORD PTR 16[ebp]
	sub	eax, DWORD PTR 12[ebp]
	mov	edx, eax
	shr	edx, 31
	add	eax, edx
	sar	eax
	mov	edx, eax
	mov	eax, DWORD PTR 12[ebp]
	add	eax, edx
	mov	DWORD PTR -12[ebp], eax
	sub	esp, 4
	push	DWORD PTR -12[ebp]
	push	DWORD PTR 12[ebp]
	push	DWORD PTR 8[ebp]
	call	mergeSort
	add	esp, 16
	sub	esp, 4
	push	DWORD PTR 16[ebp]
	push	DWORD PTR -12[ebp]
	push	DWORD PTR 8[ebp]
	call	mergeSort
	add	esp, 16
	sub	esp, 4
	push	DWORD PTR 16[ebp]
	push	DWORD PTR 12[ebp]
	push	DWORD PTR 8[ebp]
	call	merge
	add	esp, 16
	jmp	.L13
.L16:
	nop
.L13:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	mergeSort, .-mergeSort
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	lea	ecx, 4[esp]
	.cfi_def_cfa 1, 0
	and	esp, -16
	push	DWORD PTR -4[ecx]
	push	ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	mov	ebp, esp
	push	ebx
	push	ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	sub	esp, 16
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	sub	esp, 12
	push	16
	call	malloc@PLT
	add	esp, 16
	mov	DWORD PTR -12[ebp], eax
	mov	DWORD PTR -16[ebp], 0
	jmp	.L18
.L19:
	mov	eax, DWORD PTR -16[ebp]
	lea	edx, 0[0+eax*4]
	mov	eax, DWORD PTR -12[ebp]
	add	eax, edx
	mov	DWORD PTR [eax], 0
	add	DWORD PTR -16[ebp], 1
.L18:
	cmp	DWORD PTR -16[ebp], 9
	jle	.L19
	sub	esp, 4
	push	10
	push	0
	push	DWORD PTR -12[ebp]
	call	mergeSort
	add	esp, 16
	sub	esp, 12
	push	DWORD PTR -12[ebp]
	call	free@PLT
	add	esp, 16
	mov	eax, 0
	lea	esp, -8[ebp]
	pop	ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	lea	esp, -4[ecx]
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB8:
	.cfi_startproc
	mov	eax, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE8:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB9:
	.cfi_startproc
	mov	ebx, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE9:
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
