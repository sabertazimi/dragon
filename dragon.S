	.text
	.text
	.globl main


	.data
	.align 2
_Computer:
	.word 0
	.word _STRING0
	.word _Computer.crash
	.word _Computer.superMethod


	.data
	.align 2
_Mac:
	.word _Computer
	.word _STRING1
	.word _Mac.crash
	.word _Computer.superMethod


	.data
	.align 2
_OSX:
	.word _Mac
	.word _STRING2
	.word _Mac.crash
	.word _Computer.superMethod
	.word _OSX.superSuperField


	.data
	.align 2
_Expression:
	.word 0
	.word _STRING3
	.word _Expression.main


	.data
	.align 2
_Function:
	.word 0
	.word _STRING4
	.word _Function.errorRetType
	.word _Function.funcTest


	.data
	.align 2
_Statement:
	.word 0
	.word _STRING5
	.word _Statement.stmt2


	.data
	.align 2
_Variable:
	.word 0
	.word _STRING6
	.word _Variable.varTest


	.data
	.align 2
_Main:
	.word 0
	.word _STRING7
	.word main
_Computer_New:
	pushl %ebp
	movl %esp, %ebp
_Computer_New:
	jmp _Computer_New
	movl $14, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $15, %edi
	movl %eax, (%esi, %edi, 4)
	movl $16, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $16, %edi
	movl (%esi, %edi, 4), %eax
	movl $15, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $17, %edi
	leal _Computer, %eax
	movl %eax, (%esi, %edi, 4)
	movl $17, %edi
	movl (%esi, %edi, 4), %eax
	movl $15, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $15, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Mac_New:
	pushl %ebp
	movl %esp, %ebp
_Mac_New:
	jmp _Mac_New
	movl $18, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $19, %edi
	movl %eax, (%esi, %edi, 4)
	movl $20, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $20, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $20, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $21, %edi
	leal _Mac, %eax
	movl %eax, (%esi, %edi, 4)
	movl $21, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $19, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_OSX_New:
	pushl %ebp
	movl %esp, %ebp
_OSX_New:
	jmp _OSX_New
	movl $22, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $23, %edi
	movl %eax, (%esi, %edi, 4)
	movl $24, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $24, %edi
	movl (%esi, %edi, 4), %eax
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $24, %edi
	movl (%esi, %edi, 4), %eax
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $25, %edi
	leal _OSX, %eax
	movl %eax, (%esi, %edi, 4)
	movl $25, %edi
	movl (%esi, %edi, 4), %eax
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $23, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Expression_New:
	pushl %ebp
	movl %esp, %ebp
_Expression_New:
	jmp _Expression_New
	movl $26, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $27, %edi
	movl %eax, (%esi, %edi, 4)
	movl $28, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $28, %edi
	movl (%esi, %edi, 4), %eax
	movl $27, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $28, %edi
	movl (%esi, %edi, 4), %eax
	movl $27, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $29, %edi
	leal _Expression, %eax
	movl %eax, (%esi, %edi, 4)
	movl $29, %edi
	movl (%esi, %edi, 4), %eax
	movl $27, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $27, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Function_New:
	pushl %ebp
	movl %esp, %ebp
_Function_New:
	jmp _Function_New
	movl $30, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $31, %edi
	movl %eax, (%esi, %edi, 4)
	movl $32, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $32, %edi
	movl (%esi, %edi, 4), %eax
	movl $31, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $33, %edi
	leal _Function, %eax
	movl %eax, (%esi, %edi, 4)
	movl $33, %edi
	movl (%esi, %edi, 4), %eax
	movl $31, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $31, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Statement_New:
	pushl %ebp
	movl %esp, %ebp
_Statement_New:
	jmp _Statement_New
	movl $34, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $35, %edi
	movl %eax, (%esi, %edi, 4)
	movl $36, %edi
	leal _Statement, %eax
	movl %eax, (%esi, %edi, 4)
	movl $36, %edi
	movl (%esi, %edi, 4), %eax
	movl $35, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $35, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Variable_New:
	pushl %ebp
	movl %esp, %ebp
_Variable_New:
	jmp _Variable_New
	movl $37, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $38, %edi
	movl %eax, (%esi, %edi, 4)
	movl $39, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $39, %edi
	movl (%esi, %edi, 4), %eax
	movl $38, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $40, %edi
	leal _Variable, %eax
	movl %eax, (%esi, %edi, 4)
	movl $40, %edi
	movl (%esi, %edi, 4), %eax
	movl $38, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $38, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Main_New:
	pushl %ebp
	movl %esp, %ebp
_Main_New:
	jmp _Main_New
	movl $41, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $42, %edi
	movl %eax, (%esi, %edi, 4)
	movl $43, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $43, %edi
	movl (%esi, %edi, 4), %eax
	movl $42, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $44, %edi
	leal _Main, %eax
	movl %eax, (%esi, %edi, 4)
	movl $44, %edi
	movl (%esi, %edi, 4), %eax
	movl $42, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $42, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Computer.crash:
	pushl %ebp
	movl %esp, %ebp
_Computer.crash:
	jmp _Computer.crash
	call _PrintInt
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Computer.superMethod:
	pushl %ebp
	movl %esp, %ebp
_Computer.superMethod:
	jmp _Computer.superMethod
	leave
	ret

_Mac.crash:
	pushl %ebp
	movl %esp, %ebp
_Mac.crash:
	jmp _Mac.crash
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $45, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $46, %edi
	movl %eax, (%esi, %edi, 4)
	movl $46, %edi
	movl (%esi, %edi, 4), %eax
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $47, %edi
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $48, %edi
	leal_STRING8, %eax
	movl %eax, (%esi, %edi, 4)
	call _PrintString
	movl $49, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl $49, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $50, %edi
	movl %eax, (%esi, %edi, 4)
	movl $50, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_OSX.superSuperField:
	pushl %ebp
	movl %esp, %ebp
_OSX.superSuperField:
	jmp _OSX.superSuperField
	movl $5, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $51, %edi
	movl %eax, (%esi, %edi, 4)
	movl $51, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Expression.main:
	pushl %ebp
	movl %esp, %ebp
_Expression.main:
	jmp _Expression.main
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $52, %edi
	movl %eax, (%esi, %edi, 4)
	movl $53, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $54, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $53, %edi
	movl (%esi, %edi, 4), %eax
	movl $54, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $55, %edi
	movl %eax, (%esi, %edi, 4)
	movl $52, %edi
	movl (%esi, %edi, 4), %eax
	movl $55, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $56, %edi
	movl %eax, (%esi, %edi, 4)
	movl $56, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $57, %edi
	movl %eax, (%esi, %edi, 4)
	movl $58, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $59, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $53, %edi
	movl (%esi, %edi, 4), %eax
	movl $59, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $60, %edi
	movl %eax, (%esi, %edi, 4)
	movl $52, %edi
	movl (%esi, %edi, 4), %eax
	movl $60, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $61, %edi
	movl %eax, (%esi, %edi, 4)
	movl $58, %edi
	movl (%esi, %edi, 4), %eax
	movl $61, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $62, %edi
	movl %eax, (%esi, %edi, 4)
	movl $63, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $64, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $63, %edi
	movl (%esi, %edi, 4), %eax
	movl $64, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $65, %edi
	movl %eax, (%esi, %edi, 4)
	movl $62, %edi
	movl (%esi, %edi, 4), %eax
	movl $65, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $66, %edi
	movl %eax, (%esi, %edi, 4)
	movl $66, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $67, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $68, %edi
	movl %eax, (%esi, %edi, 4)
	movl $69, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $70, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $69, %edi
	movl (%esi, %edi, 4), %eax
	movl $70, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $71, %edi
	movl %eax, (%esi, %edi, 4)
	movl $68, %edi
	movl (%esi, %edi, 4), %eax
	movl $71, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $72, %edi
	movl %eax, (%esi, %edi, 4)
	movl $72, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $73, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $74, %edi
	movl %eax, (%esi, %edi, 4)
	movl $75, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $76, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $75, %edi
	movl (%esi, %edi, 4), %eax
	movl $76, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $77, %edi
	movl %eax, (%esi, %edi, 4)
	movl $74, %edi
	movl (%esi, %edi, 4), %eax
	movl $77, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $78, %edi
	movl %eax, (%esi, %edi, 4)
	movl $78, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $79, %edi
	movl %eax, (%esi, %edi, 4)
	movl $73, %edi
	movl (%esi, %edi, 4), %eax
	movl $79, %edi
	movl (%esi, %edi, 4), %ebx
	orl %ebx, %eax
	movl $80, %edi
	movl %eax, (%esi, %edi, 4)
	movl $81, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $63, %edi
	movl (%esi, %edi, 4), %eax
	movl $81, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $82, %edi
	movl %eax, (%esi, %edi, 4)
	movl $62, %edi
	movl (%esi, %edi, 4), %eax
	movl $82, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $83, %edi
	movl %eax, (%esi, %edi, 4)
	movl $80, %edi
	movl (%esi, %edi, 4), %eax
	movl $83, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $84, %edi
	movl %eax, (%esi, %edi, 4)
	movl $85, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $86, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $85, %edi
	movl (%esi, %edi, 4), %eax
	movl $86, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $87, %edi
	movl %eax, (%esi, %edi, 4)
	movl $84, %edi
	movl (%esi, %edi, 4), %eax
	movl $87, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $88, %edi
	movl %eax, (%esi, %edi, 4)
	movl $88, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $89, %edi
	movl %eax, (%esi, %edi, 4)
	movl $90, %edi
	movl $233, %eax
	movl %eax, (%esi, %edi, 4)
	movl $91, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $85, %edi
	movl (%esi, %edi, 4), %eax
	movl $91, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $92, %edi
	movl %eax, (%esi, %edi, 4)
	movl $84, %edi
	movl (%esi, %edi, 4), %eax
	movl $92, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $93, %edi
	movl %eax, (%esi, %edi, 4)
	movl $90, %edi
	movl (%esi, %edi, 4), %eax
	movl $93, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $94, %edi
	movl %eax, (%esi, %edi, 4)
	movl $95, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $96, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $95, %edi
	movl (%esi, %edi, 4), %eax
	movl $96, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $97, %edi
	movl %eax, (%esi, %edi, 4)
	movl $94, %edi
	movl (%esi, %edi, 4), %eax
	movl $97, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $98, %edi
	movl %eax, (%esi, %edi, 4)
	movl $98, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $99, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $100, %edi
	movl %eax, (%esi, %edi, 4)
	movl $101, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $102, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $101, %edi
	movl (%esi, %edi, 4), %eax
	movl $102, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $103, %edi
	movl %eax, (%esi, %edi, 4)
	movl $100, %edi
	movl (%esi, %edi, 4), %eax
	movl $103, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $104, %edi
	movl %eax, (%esi, %edi, 4)
	movl $104, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $105, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $106, %edi
	movl %eax, (%esi, %edi, 4)
	movl $107, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $108, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $107, %edi
	movl (%esi, %edi, 4), %eax
	movl $108, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $109, %edi
	movl %eax, (%esi, %edi, 4)
	movl $106, %edi
	movl (%esi, %edi, 4), %eax
	movl $109, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $110, %edi
	movl %eax, (%esi, %edi, 4)
	movl $110, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $111, %edi
	movl %eax, (%esi, %edi, 4)
	movl $105, %edi
	movl (%esi, %edi, 4), %eax
	movl $111, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $112, %edi
	movl %eax, (%esi, %edi, 4)
	movl $113, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $95, %edi
	movl (%esi, %edi, 4), %eax
	movl $113, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $114, %edi
	movl %eax, (%esi, %edi, 4)
	movl $94, %edi
	movl (%esi, %edi, 4), %eax
	movl $114, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $115, %edi
	movl %eax, (%esi, %edi, 4)
	movl $112, %edi
	movl (%esi, %edi, 4), %eax
	movl $115, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $117, %edi
	movl %eax, (%esi, %edi, 4)
	movl $118, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $119, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $118, %edi
	movl (%esi, %edi, 4), %eax
	movl $119, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $120, %edi
	movl %eax, (%esi, %edi, 4)
	movl $117, %edi
	movl (%esi, %edi, 4), %eax
	movl $120, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $121, %edi
	movl %eax, (%esi, %edi, 4)
	movl $121, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $122, %edi
	movl %eax, (%esi, %edi, 4)
	movl $122, %edi
	movl (%esi, %edi, 4), %eax
	negl %eax
	movl $123, %edi
	movl %eax, (%esi, %edi, 4)
	movl $123, %edi
	movl (%esi, %edi, 4), %eax
	movl $116, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $125, %edi
	movl %eax, (%esi, %edi, 4)
	movl $126, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $127, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $126, %edi
	movl (%esi, %edi, 4), %eax
	movl $127, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $128, %edi
	movl %eax, (%esi, %edi, 4)
	movl $125, %edi
	movl (%esi, %edi, 4), %eax
	movl $128, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $129, %edi
	movl %eax, (%esi, %edi, 4)
	movl $129, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $130, %edi
	movl %eax, (%esi, %edi, 4)
	movl $130, %edi
	movl (%esi, %edi, 4), %eax
	notl %eax
	movl $131, %edi
	movl %eax, (%esi, %edi, 4)
	movl $131, %edi
	movl (%esi, %edi, 4), %eax
	movl $124, %edi
	movl %eax, (%esi, %edi, 4)
	movl $136, %edi
	movl $3, %eax
	movl %eax, (%esi, %edi, 4)
	movl $136, %edi
	movl (%esi, %edi, 4), %eax
	movl $132, %edi
	movl %eax, (%esi, %edi, 4)
	movl $137, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $137, %edi
	movl (%esi, %edi, 4), %eax
	movl $133, %edi
	movl %eax, (%esi, %edi, 4)
	movl $138, %edi
	movl $3, %eax
	movl %eax, (%esi, %edi, 4)
	movl $139, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $140, %edi
	movl $7, %eax
	movl %eax, (%esi, %edi, 4)
	movl $140, %edi
	movl (%esi, %edi, 4), %eax
	movl $134, %edi
	movl %eax, (%esi, %edi, 4)
	movl $141, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	movl $141, %edi
	movl (%esi, %edi, 4), %eax
	movl $134, %edi
	movl %eax, (%esi, %edi, 4)
	movl $142, %edi
	movl $5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $135, %edi
	movl %eax, (%esi, %edi, 4)

_Function.funcTest:
	pushl %ebp
	movl %esp, %ebp
_Function.funcTest:
	jmp _Function.funcTest
	movl $144, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $144, %edi
	movl (%esi, %edi, 4), %eax
	movl $8, %edi
	movl %eax, (%esi, %edi, 4)
	movl $8, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Function.errorRetType:
	pushl %ebp
	movl %esp, %ebp
_Function.errorRetType:
	jmp _Function.errorRetType
	movl $145, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $145, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

_Statement.stmt2:
	pushl %ebp
	movl %esp, %ebp
_Statement.stmt2:
	jmp _Statement.stmt2
_L25:
	jmp _L25
	movl $147, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $146, %edi
	movl (%esi, %edi, 4), %eax
	movl $147, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setg %al
	movzbl %al, %eax
	movl $148, %edi
	movl %eax, (%esi, %edi, 4)
	movl $148%edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je_L26
	movl $150, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $146, %edi
	movl (%esi, %edi, 4), %eax
	movl $150, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $151, %edi
	movl %eax, (%esi, %edi, 4)
	movl $151, %edi
	movl (%esi, %edi, 4), %eax
	movl $146, %edi
	movl %eax, (%esi, %edi, 4)
	movl $152, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $146, %edi
	movl (%esi, %edi, 4), %eax
	movl $152, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $153, %edi
	movl %eax, (%esi, %edi, 4)
	movl $153, %edi
	movl (%esi, %edi, 4), %eax
	movl $149, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L25
_L26:
	jmp _L26
_L27:
	jmp _L27
	movl $154, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $146, %edi
	movl (%esi, %edi, 4), %eax
	movl $154, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setl %al
	movzbl %al, %eax
	movl $155, %edi
	movl %eax, (%esi, %edi, 4)
	movl $155%edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je_L28
	movl $157, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $156, %edi
	movl (%esi, %edi, 4), %eax
	movl $157, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $158, %edi
	movl %eax, (%esi, %edi, 4)
	movl $158, %edi
	movl (%esi, %edi, 4), %eax
	movl $156, %edi
	movl %eax, (%esi, %edi, 4)
	movl $159, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $146, %edi
	movl (%esi, %edi, 4), %eax
	movl $159, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $160, %edi
	movl %eax, (%esi, %edi, 4)
	movl $160, %edi
	movl (%esi, %edi, 4), %eax
	movl $146, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L27
_L28:
	jmp _L28
	movl $161, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $161, %edi
	movl (%esi, %edi, 4), %eax
	movl $146, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L29
_L30:
	jmp _L30
	movl $162, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $163, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $163, %edi
	movl (%esi, %edi, 4), %eax
	movl $146, %edi
	movl %eax, (%esi, %edi, 4)
_L29:
	jmp _L29
	movl $164, %edi
	movl $10, %eax
	movl %eax, (%esi, %edi, 4)
	movl $165, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $165%edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je_L31
	call _PrintInt
	jmp _L30
_L31:
	jmp _L31

_Variable.varTest:
	pushl %ebp
	movl %esp, %ebp
_Variable.varTest:
	jmp _Variable.varTest
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $166, %edi
	movl %eax, (%esi, %edi, 4)
	movl $167, %edi
	movl $5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $168, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $168, %edi
	movl (%esi, %edi, 4), %eax
	movl $167, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $169, %edi
	movl %eax, (%esi, %edi, 4)
	movl $168, %edi
	movl (%esi, %edi, 4), %eax
	movl $169, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $170, %edi
	movl %eax, (%esi, %edi, 4)
	call _Alloc
	movl $171, %edi
	movl %eax, (%esi, %edi, 4)
	movl $167, %edi
	movl (%esi, %edi, 4), %eax
	movl $171, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $172, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $171, %edi
	movl (%esi, %edi, 4), %eax
	movl $170, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $171, %edi
	movl %eax, (%esi, %edi, 4)
_L32:
	jmp _L32
	movl $170, %edi
	movl (%esi, %edi, 4), %eax
	movl $168, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $170, %edi
	movl %eax, (%esi, %edi, 4)
	movl $170%edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je_L33
	movl $171, %edi
	movl (%esi, %edi, 4), %eax
	movl $168, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $171, %edi
	movl %eax, (%esi, %edi, 4)
	movl $172, %edi
	movl (%esi, %edi, 4), %eax
	movl $171, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	jmp _L32
_L33:
	jmp _L33
	movl $171, %edi
	movl (%esi, %edi, 4), %eax
	movl $12, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edi
	movl (%esi, %edi, 4), %ecx
	movl %eax, (%ebx, %ecx, 1)
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $173, %edi
	movl %eax, (%esi, %edi, 4)
	movl $174, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $175, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $174, %edi
	movl (%esi, %edi, 4), %eax
	movl $175, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $176, %edi
	movl %eax, (%esi, %edi, 4)
	movl $173, %edi
	movl (%esi, %edi, 4), %eax
	movl $176, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $177, %edi
	movl %eax, (%esi, %edi, 4)
	movl $177, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $178, %edi
	movl %eax, (%esi, %edi, 4)
	movl $179, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $180, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $179, %edi
	movl (%esi, %edi, 4), %eax
	movl $180, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $181, %edi
	movl %eax, (%esi, %edi, 4)
	movl $178, %edi
	movl (%esi, %edi, 4), %eax
	movl $181, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $182, %edi
	movl %eax, (%esi, %edi, 4)
	movl $182, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $183, %edi
	movl %eax, (%esi, %edi, 4)
	movl $183, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

main:
	pushl %ebp
	movl %esp, %ebp
	pushl $4000       # 4000/4 = 1000 fake registers
	call malloc
	movl %eax, %esi   # store registers base into %esi
main:
	jmp main
	movl $13, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $185, %edi
	movl %eax, (%esi, %edi, 4)
	movl $185, %edi
	movl (%esi, %edi, 4), %eax
	movl $184, %edi
	movl %eax, (%esi, %edi, 4)
	call _Mac_New
	movl $187, %edi
	movl %eax, (%esi, %edi, 4)
	movl $187, %edi
	movl (%esi, %edi, 4), %eax
	movl $186, %edi
	movl %eax, (%esi, %edi, 4)
	movl $188, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $186, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $189, %edi
	movl %eax, (%esi, %edi, 4)
	movl $189, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $190, %edi
	movl %eax, (%esi, %edi, 4)
	movl $190, %edi
	movl (%esi, %edi, 4), %eax
	call *%eax
	movl $191, %edi
	movl %eax, (%esi, %edi, 4)
	movl $186, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $192, %edi
	movl %eax, (%esi, %edi, 4)
	movl $192, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $193, %edi
	movl %eax, (%esi, %edi, 4)
	movl $193, %edi
	movl (%esi, %edi, 4), %eax
	call *%eax
	call _Function_New
	movl $195, %edi
	movl %eax, (%esi, %edi, 4)
	movl $195, %edi
	movl (%esi, %edi, 4), %eax
	movl $194, %edi
	movl %eax, (%esi, %edi, 4)
	movl $196, %edi
	movl $3, %eax
	movl %eax, (%esi, %edi, 4)
	movl $184, %edi
	movl (%esi, %edi, 4), %eax
	movl $196, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $197, %edi
	movl %eax, (%esi, %edi, 4)
	movl $194, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $198, %edi
	movl %eax, (%esi, %edi, 4)
	movl $198, %edi
	movl (%esi, %edi, 4), %eax
	movl $0, %edi
	movl (%esi, %edi, 4), %ebx
	movl (%eax, %ebx, 1), %eax
	movl $199, %edi
	movl %eax, (%esi, %edi, 4)
	movl $199, %edi
	movl (%esi, %edi, 4), %eax
	call *%eax
	movl $200, %edi
	movl %eax, (%esi, %edi, 4)


	.data
_STRING0:
	.asciiz Computer
_STRING3:
	.asciiz Expression
_STRING4:
	.asciiz Function
_STRING1:
	.asciiz Mac
_STRING7:
	.asciiz Main
_STRING2:
	.asciiz OSX
_STRING5:
	.asciiz Statement
_STRING6:
	.asciiz Variable
_STRING8:
	.asciiz ack!
