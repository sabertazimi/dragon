	.data
	.align 2
_Computer:
	.long 0
	.long _STRING0
	.long _Computer.crash


	.data
	.align 2
_Mac:
	.long _Computer
	.long _STRING1
	.long _Mac.crash


	.data
	.align 2
_Linux:
	.long _Mac
	.long _STRING2
	.long _Linux.crash


	.data
	.align 2
_Main:
	.long 0
	.long _STRING3
	.long main



	.text
	.global _Computer_New
_Computer_New:
	pushl %ebp
	movl %esp, %ebp
	movl $4, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $5, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $5, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $7, %edi
	leal _Computer, %eax
	movl %eax, (%esi, %edi, 4)
	movl $7, %edi
	movl (%esi, %edi, 4), %eax
	movl $5, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $5, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Mac_New
_Mac_New:
	pushl %ebp
	movl %esp, %ebp
	movl $8, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	movl $8, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $9, %edi
	movl %eax, (%esi, %edi, 4)
	movl $10, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $10, %edi
	movl (%esi, %edi, 4), %eax
	movl $9, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $10, %edi
	movl (%esi, %edi, 4), %eax
	movl $9, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 8(%ebx)
	movl $11, %edi
	leal _Mac, %eax
	movl %eax, (%esi, %edi, 4)
	movl $11, %edi
	movl (%esi, %edi, 4), %eax
	movl $9, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $9, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Linux_New
_Linux_New:
	pushl %ebp
	movl %esp, %ebp
	movl $12, %edi
	movl $16, %eax
	movl %eax, (%esi, %edi, 4)
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $13, %edi
	movl %eax, (%esi, %edi, 4)
	movl $14, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $14, %edi
	movl (%esi, %edi, 4), %eax
	movl $13, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $14, %edi
	movl (%esi, %edi, 4), %eax
	movl $13, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 8(%ebx)
	movl $14, %edi
	movl (%esi, %edi, 4), %eax
	movl $13, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 12(%ebx)
	movl $15, %edi
	leal _Linux, %eax
	movl %eax, (%esi, %edi, 4)
	movl $15, %edi
	movl (%esi, %edi, 4), %eax
	movl $13, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $13, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Computer.crash
_Computer.crash:
	pushl %ebp
	movl %esp, %ebp
	movl $16, %edi
	leal _STRING4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $16, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintString
	leave
	ret

	.global _Mac.crash
_Mac.crash:
	pushl %ebp
	movl %esp, %ebp
	movl $17, %edi
	leal _STRING5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $17, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintString
	leave
	ret

	.global _Linux.crash
_Linux.crash:
	pushl %ebp
	movl %esp, %ebp
	movl $18, %edi
	leal _STRING6, %eax
	movl %eax, (%esi, %edi, 4)
	movl $18, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintString
	leave
	ret

	.global main
main:
	pushl %ebp
	movl %esp, %ebp
	pushl $4000       # 4000/4 = 1000 fake registers
	call malloc
	movl %eax, %esi   # store registers base into %esi
	call _Mac_New
	movl $22, %edi
	movl %eax, (%esi, %edi, 4)
	movl $22, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl %eax, (%esi, %edi, 4)
	movl $19, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $23, %edi
	movl %eax, (%esi, %edi, 4)
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $24, %edi
	movl %eax, (%esi, %edi, 4)
	movl $24, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, %edi
	call *%edi
	call _Linux_New
	movl $25, %edi
	movl %eax, (%esi, %edi, 4)
	movl $25, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl %eax, (%esi, %edi, 4)
	movl $19, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $26, %edi
	movl %eax, (%esi, %edi, 4)
	movl $26, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $27, %edi
	movl %eax, (%esi, %edi, 4)
	movl $27, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, %edi
	call *%edi
	leave
	pushl $0
	call exit


	.data
_STRING0:
	.string "Computer"
_STRING4:
	.string "Computer Crash!"
_STRING2:
	.string "Linux"
_STRING6:
	.string "Linux Crash!"
_STRING1:
	.string "Mac"
_STRING5:
	.string "Mac Crash!"
_STRING3:
	.string "Main"
intFormat:
	.string "%d\n"
trues:
	.string "true\n"
falses:
	.string "false\n"
stringFormat:
	.string "%s\n"
readBuf:
	.string "00000000000000000000000000000000000000000000000000\0"
readFormat:
	.string "%s"

	.text
	.global _ReadInteger
_ReadInteger:
	pushl %ebp
	movl %esp, %ebp
	leal readBuf, %eax
	pushl %eax
	pushl $readFormat
	call scanf
	popl %ebx
	popl %ebx
	leal readBuf, %eax
	pushl %eax
	call atoi
	popl %ebx
	popl %ebx
	leave
	ret
	.global _ReadLine
_ReadLine:
	pushl %ebp
	movl %esp, %ebp
	leal readBuf, %eax
	pushl %eax
	pushl $readFormat
	call scanf
	popl %ebx
	popl %ebx
	leal readBuf, %eax
	leave
	ret
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
