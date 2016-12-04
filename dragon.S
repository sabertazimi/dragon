	.data
	.align 4
_Main:
	.long 0
	.long _STRING0
	.long main



	.text
	.global main
main:
	pushl %ebp
	movl %esp, %ebp
	pushl $4000       # 4000/4 = 1000 fake registers
	call malloc
	movl %eax, %esi   # store registers base into %esi
	movl $4, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $5, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $5, %edi
	movl (%esi, %edi, 4), %eax
	movl $1, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L8
_L9:
	movl $6, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $7, %edi
	movl %eax, (%esi, %edi, 4)
	movl $7, %edi
	movl (%esi, %edi, 4), %eax
	movl $1, %edi
	movl %eax, (%esi, %edi, 4)
_L8:
	movl $8, %edi
	movl $5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	movl $8, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setl %al
	movzbl %al, %eax
	movl $9, %edi
	movl %eax, (%esi, %edi, 4)
	movl $9, %edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je _L10
	movl $10, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $10, %edi
	movl (%esi, %edi, 4), %eax
	movl $2, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L11
_L12:
	movl $11, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $2, %edi
	movl (%esi, %edi, 4), %eax
	movl $11, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $12, %edi
	movl %eax, (%esi, %edi, 4)
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	movl $2, %edi
	movl %eax, (%esi, %edi, 4)
_L11:
	movl $13, %edi
	movl $5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $2, %edi
	movl (%esi, %edi, 4), %eax
	movl $13, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setl %al
	movzbl %al, %eax
	movl $14, %edi
	movl %eax, (%esi, %edi, 4)
	movl $14, %edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je _L13
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl $2, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $15, %edi
	movl %eax, (%esi, %edi, 4)
	movl $15, %edi
	movl (%esi, %edi, 4), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintInt
	jmp _L12
_L13:
	jmp _L9
_L10:
	leave
	pushl $0
	call exit


	.data
_STRING0:
	.string "Main"
intFormat:
	.string "%d\n"
trues:
	.string "true\n"
falses:
	.string "false\n"
stringFormat:
	.string "%s\n"

	.text
	.global _PrintInt
_PrintInt:
	pushl %ebp
	movl %esp, %ebp
	pushl 8(%ebp)
	pushl $intFormat
	call printf
	popl %eax
	popl %eax
	leave
	ret
	.global _PrintBool
_PrintBool:
	pushl %ebp
	movl %esp, %ebp
	xorl %eax, %eax
	cmpl 8(%ebp), %eax
	je .L_f
	pushl $trues
	jmp .L_e
.L_f:
	pushl $falses
.L_e:
	call printf
	leave
	ret
	.global _PrintString
_PrintString:
	pushl %ebp
	movl %esp, %ebp
	pushl 8(%ebp)
	pushl $stringFormat
	call printf
	popl %eax
	popl %eax
	leave
	ret
