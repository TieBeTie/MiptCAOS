	.file	"main.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%d "
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
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
	sub	esp, 1616
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR gs:20
	mov	DWORD PTR -12[ebp], eax
	xor	eax, eax
	sub	esp, 8
	lea	eax, -1624[ebp]
	push	eax
	lea	eax, .LC0@GOTOFF[ebx]
	push	eax
	call	__isoc99_scanf@PLT
	add	esp, 16
	mov	DWORD PTR -1620[ebp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -1620[ebp]
	lea	edx, 0[0+eax*4]
	lea	eax, -1612[ebp]
	add	eax, edx
	sub	esp, 8
	push	eax
	lea	eax, .LC0@GOTOFF[ebx]
	push	eax
	call	__isoc99_scanf@PLT
	add	esp, 16
	add	DWORD PTR -1620[ebp], 1
.L2:
	mov	eax, DWORD PTR -1624[ebp]
	cmp	DWORD PTR -1620[ebp], eax
	jl	.L3
	mov	eax, DWORD PTR -1624[ebp]
	lea	edx, -812[ebp]
	push	edx
	lea	edx, -1612[ebp]
	push	edx
	push	eax
	push	0
	call	merge_sort@PLT
	add	esp, 16
	mov	DWORD PTR -1616[ebp], 0
	jmp	.L4
.L5:
	mov	eax, DWORD PTR -1616[ebp]
	lea	edx, 0[0+eax*4]
	lea	eax, -812[ebp]
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	sub	esp, 8
	push	eax
	lea	eax, .LC1@GOTOFF[ebx]
	push	eax
	call	printf@PLT
	add	esp, 16
	add	DWORD PTR -1616[ebp], 1
.L4:
	mov	eax, DWORD PTR -1624[ebp]
	cmp	DWORD PTR -1616[ebp], eax
	jl	.L5
	mov	eax, 0
	mov	ecx, DWORD PTR -12[ebp]
	xor	ecx, DWORD PTR gs:20
	je	.L7
	call	__stack_chk_fail_local
.L7:
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
.LFE0:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB1:
	.cfi_startproc
	mov	ebx, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE1:
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
