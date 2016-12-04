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
	movl $1, %edi
	leal _STRING1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintString
	leave
	pushl $0
	call exit


	.data
_STRING0:
	.string "Main"
_STRING1:
	.string "ack!"
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
