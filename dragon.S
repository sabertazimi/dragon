	.data
	.align 2
_Computer:
	.long 0
	.long _STRING0
	.long _Computer.crash
	.long _Computer.superMethod


	.data
	.align 2
_Mac:
	.long _Computer
	.long _STRING1
	.long _Mac.crash
	.long _Computer.superMethod


	.data
	.align 2
_OSX:
	.long _Mac
	.long _STRING2
	.long _Mac.crash
	.long _Computer.superMethod
	.long _OSX.superSuperField


	.data
	.align 2
_Expression:
	.long 0
	.long _STRING3
	.long _Expression.main


	.data
	.align 2
_Function:
	.long 0
	.long _STRING4
	.long _Function.errorRetType
	.long _Function.funcTest


	.data
	.align 2
_Statement:
	.long 0
	.long _STRING5
	.long _Statement.stmt2


	.data
	.align 2
_Variable:
	.long 0
	.long _STRING6
	.long _Variable.varTest


	.data
	.align 2
_Main:
	.long 0
	.long _STRING7
	.long main



	.text
	.global _Computer_New
_Computer_New:
	pushl %ebp
	movl %esp, %ebp
	movl $14, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	movl $14, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $15, %edi
	movl %eax, (%esi, %edi, 4)
	movl $16, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $16, %edi
	movl (%esi, %edi, 4), %eax
	movl $15, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $17, %edi
	leal _Computer, %eax
	movl %eax, (%esi, %edi, 4)
	movl $17, %edi
	movl (%esi, %edi, 4), %eax
	movl $15, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $15, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Mac_New
_Mac_New:
	pushl %ebp
	movl %esp, %ebp
	movl $18, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	movl $18, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $19, %edi
	movl %eax, (%esi, %edi, 4)
	movl $20, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $20, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $20, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 8(%ebx)
	movl $21, %edi
	leal _Mac, %eax
	movl %eax, (%esi, %edi, 4)
	movl $21, %edi
	movl (%esi, %edi, 4), %eax
	movl $19, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $19, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _OSX_New
_OSX_New:
	pushl %ebp
	movl %esp, %ebp
	movl $22, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	movl $22, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $23, %edi
	movl %eax, (%esi, %edi, 4)
	movl $24, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $24, %edi
	movl (%esi, %edi, 4), %eax
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $24, %edi
	movl (%esi, %edi, 4), %eax
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 8(%ebx)
	movl $25, %edi
	leal _OSX, %eax
	movl %eax, (%esi, %edi, 4)
	movl $25, %edi
	movl (%esi, %edi, 4), %eax
	movl $23, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $23, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Expression_New
_Expression_New:
	pushl %ebp
	movl %esp, %ebp
	movl $26, %edi
	movl $12, %eax
	movl %eax, (%esi, %edi, 4)
	movl $26, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $27, %edi
	movl %eax, (%esi, %edi, 4)
	movl $28, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $28, %edi
	movl (%esi, %edi, 4), %eax
	movl $27, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $28, %edi
	movl (%esi, %edi, 4), %eax
	movl $27, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 8(%ebx)
	movl $29, %edi
	leal _Expression, %eax
	movl %eax, (%esi, %edi, 4)
	movl $29, %edi
	movl (%esi, %edi, 4), %eax
	movl $27, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $27, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Function_New
_Function_New:
	pushl %ebp
	movl %esp, %ebp
	movl $30, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	movl $30, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $31, %edi
	movl %eax, (%esi, %edi, 4)
	movl $32, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $32, %edi
	movl (%esi, %edi, 4), %eax
	movl $31, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $33, %edi
	leal _Function, %eax
	movl %eax, (%esi, %edi, 4)
	movl $33, %edi
	movl (%esi, %edi, 4), %eax
	movl $31, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $31, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Statement_New
_Statement_New:
	pushl %ebp
	movl %esp, %ebp
	movl $34, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $34, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $35, %edi
	movl %eax, (%esi, %edi, 4)
	movl $36, %edi
	leal _Statement, %eax
	movl %eax, (%esi, %edi, 4)
	movl $36, %edi
	movl (%esi, %edi, 4), %eax
	movl $35, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $35, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Variable_New
_Variable_New:
	pushl %ebp
	movl %esp, %ebp
	movl $37, %edi
	movl $8, %eax
	movl %eax, (%esi, %edi, 4)
	movl $37, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $38, %edi
	movl %eax, (%esi, %edi, 4)
	movl $39, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $39, %edi
	movl (%esi, %edi, 4), %eax
	movl $38, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $40, %edi
	leal _Variable, %eax
	movl %eax, (%esi, %edi, 4)
	movl $40, %edi
	movl (%esi, %edi, 4), %eax
	movl $38, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $38, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Computer.crash
_Computer.crash:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl $1, %edi
	movl %eax, (%esi, %edi, 4)
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	call _PrintInt
	movl 8(%ebp), %eax
	movl $1, %edi
	movl %eax, (%esi, %edi, 4)
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret
	movl $1, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)

	.global _Computer.superMethod
_Computer.superMethod:
	pushl %ebp
	movl %esp, %ebp
	leave
	ret

	.global _Mac.crash
_Mac.crash:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $41, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl 8(%ebp), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $42, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl 8(%ebp), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $42, %edi
	movl (%esi, %edi, 4), %eax
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 8(%ebx)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl 8(%ebp), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $43, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl 8(%ebp), %eax
	movl $4, %edi
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $44, %edi
	leal _STRING8, %eax
	movl %eax, (%esi, %edi, 4)
	movl $44, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintString
	movl 8(%ebp), %eax
	movl $3, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $45, %edi
	movl %eax, (%esi, %edi, 4)
	movl $3, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $45, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintInt
	movl $46, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $4, %edi
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl $46, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $47, %edi
	movl %eax, (%esi, %edi, 4)
	movl $4, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $47, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _OSX.superSuperField
_OSX.superSuperField:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl $5, %edi
	movl %eax, (%esi, %edi, 4)
	movl $5, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $48, %edi
	movl %eax, (%esi, %edi, 4)
	movl $5, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $48, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Expression.main
_Expression.main:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $49, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $50, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $51, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $50, %edi
	movl (%esi, %edi, 4), %eax
	movl $51, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $52, %edi
	movl %eax, (%esi, %edi, 4)
	movl $49, %edi
	movl (%esi, %edi, 4), %eax
	movl $52, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $53, %edi
	movl %eax, (%esi, %edi, 4)
	movl $53, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $54, %edi
	movl %eax, (%esi, %edi, 4)
	movl $55, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $56, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $50, %edi
	movl (%esi, %edi, 4), %eax
	movl $56, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $57, %edi
	movl %eax, (%esi, %edi, 4)
	movl $49, %edi
	movl (%esi, %edi, 4), %eax
	movl $57, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $58, %edi
	movl %eax, (%esi, %edi, 4)
	movl $55, %edi
	movl (%esi, %edi, 4), %eax
	movl $58, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $59, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $60, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $61, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $60, %edi
	movl (%esi, %edi, 4), %eax
	movl $61, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $62, %edi
	movl %eax, (%esi, %edi, 4)
	movl $59, %edi
	movl (%esi, %edi, 4), %eax
	movl $62, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $63, %edi
	movl %eax, (%esi, %edi, 4)
	movl $63, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $64, %edi
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $65, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $66, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $67, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $66, %edi
	movl (%esi, %edi, 4), %eax
	movl $67, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $68, %edi
	movl %eax, (%esi, %edi, 4)
	movl $65, %edi
	movl (%esi, %edi, 4), %eax
	movl $68, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $69, %edi
	movl %eax, (%esi, %edi, 4)
	movl $69, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $70, %edi
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $71, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $72, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $73, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $72, %edi
	movl (%esi, %edi, 4), %eax
	movl $73, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $74, %edi
	movl %eax, (%esi, %edi, 4)
	movl $71, %edi
	movl (%esi, %edi, 4), %eax
	movl $74, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $75, %edi
	movl %eax, (%esi, %edi, 4)
	movl $75, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $76, %edi
	movl %eax, (%esi, %edi, 4)
	movl $70, %edi
	movl (%esi, %edi, 4), %eax
	movl $76, %edi
	movl (%esi, %edi, 4), %ebx
	orl %ebx, %eax
	movl $77, %edi
	movl %eax, (%esi, %edi, 4)
	movl $78, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $60, %edi
	movl (%esi, %edi, 4), %eax
	movl $78, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $79, %edi
	movl %eax, (%esi, %edi, 4)
	movl $59, %edi
	movl (%esi, %edi, 4), %eax
	movl $79, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $80, %edi
	movl %eax, (%esi, %edi, 4)
	movl $77, %edi
	movl (%esi, %edi, 4), %eax
	movl $80, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $81, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $82, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $83, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $82, %edi
	movl (%esi, %edi, 4), %eax
	movl $83, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $84, %edi
	movl %eax, (%esi, %edi, 4)
	movl $81, %edi
	movl (%esi, %edi, 4), %eax
	movl $84, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $85, %edi
	movl %eax, (%esi, %edi, 4)
	movl $85, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $86, %edi
	movl %eax, (%esi, %edi, 4)
	movl $87, %edi
	movl $233, %eax
	movl %eax, (%esi, %edi, 4)
	movl $88, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $82, %edi
	movl (%esi, %edi, 4), %eax
	movl $88, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $89, %edi
	movl %eax, (%esi, %edi, 4)
	movl $81, %edi
	movl (%esi, %edi, 4), %eax
	movl $89, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $90, %edi
	movl %eax, (%esi, %edi, 4)
	movl $87, %edi
	movl (%esi, %edi, 4), %eax
	movl $90, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $91, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $92, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $93, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $92, %edi
	movl (%esi, %edi, 4), %eax
	movl $93, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $94, %edi
	movl %eax, (%esi, %edi, 4)
	movl $91, %edi
	movl (%esi, %edi, 4), %eax
	movl $94, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $95, %edi
	movl %eax, (%esi, %edi, 4)
	movl $95, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $96, %edi
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $97, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $98, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $99, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $98, %edi
	movl (%esi, %edi, 4), %eax
	movl $99, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $100, %edi
	movl %eax, (%esi, %edi, 4)
	movl $97, %edi
	movl (%esi, %edi, 4), %eax
	movl $100, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $101, %edi
	movl %eax, (%esi, %edi, 4)
	movl $101, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $102, %edi
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $103, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $104, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $105, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $104, %edi
	movl (%esi, %edi, 4), %eax
	movl $105, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $106, %edi
	movl %eax, (%esi, %edi, 4)
	movl $103, %edi
	movl (%esi, %edi, 4), %eax
	movl $106, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $107, %edi
	movl %eax, (%esi, %edi, 4)
	movl $107, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $108, %edi
	movl %eax, (%esi, %edi, 4)
	movl $102, %edi
	movl (%esi, %edi, 4), %eax
	movl $108, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $109, %edi
	movl %eax, (%esi, %edi, 4)
	movl $110, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $92, %edi
	movl (%esi, %edi, 4), %eax
	movl $110, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $111, %edi
	movl %eax, (%esi, %edi, 4)
	movl $91, %edi
	movl (%esi, %edi, 4), %eax
	movl $111, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $112, %edi
	movl %eax, (%esi, %edi, 4)
	movl $109, %edi
	movl (%esi, %edi, 4), %eax
	movl $112, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $114, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $115, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $116, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $115, %edi
	movl (%esi, %edi, 4), %eax
	movl $116, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $117, %edi
	movl %eax, (%esi, %edi, 4)
	movl $114, %edi
	movl (%esi, %edi, 4), %eax
	movl $117, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $118, %edi
	movl %eax, (%esi, %edi, 4)
	movl $118, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $119, %edi
	movl %eax, (%esi, %edi, 4)
	movl $119, %edi
	movl (%esi, %edi, 4), %eax
	negl %eax
	movl $120, %edi
	movl %eax, (%esi, %edi, 4)
	movl $120, %edi
	movl (%esi, %edi, 4), %eax
	movl $113, %edi
	movl %eax, (%esi, %edi, 4)
	movl 8(%ebp), %eax
	movl $6, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $122, %edi
	movl %eax, (%esi, %edi, 4)
	movl $6, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $123, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $124, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $123, %edi
	movl (%esi, %edi, 4), %eax
	movl $124, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $125, %edi
	movl %eax, (%esi, %edi, 4)
	movl $122, %edi
	movl (%esi, %edi, 4), %eax
	movl $125, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $126, %edi
	movl %eax, (%esi, %edi, 4)
	movl $126, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $127, %edi
	movl %eax, (%esi, %edi, 4)
	movl $127, %edi
	movl (%esi, %edi, 4), %eax
	notl %eax
	movl $128, %edi
	movl %eax, (%esi, %edi, 4)
	movl $128, %edi
	movl (%esi, %edi, 4), %eax
	movl $121, %edi
	movl %eax, (%esi, %edi, 4)
	movl $133, %edi
	movl $3, %eax
	movl %eax, (%esi, %edi, 4)
	movl $133, %edi
	movl (%esi, %edi, 4), %eax
	movl $129, %edi
	movl %eax, (%esi, %edi, 4)
	movl $134, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $134, %edi
	movl (%esi, %edi, 4), %eax
	movl $130, %edi
	movl %eax, (%esi, %edi, 4)
	movl $135, %edi
	movl $3, %eax
	movl %eax, (%esi, %edi, 4)
	movl $136, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $137, %edi
	movl $7, %eax
	movl %eax, (%esi, %edi, 4)
	movl $137, %edi
	movl (%esi, %edi, 4), %eax
	movl $131, %edi
	movl %eax, (%esi, %edi, 4)
	movl $129, %edi
	movl (%esi, %edi, 4), %eax
	movl $130, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $138, %edi
	movl %eax, (%esi, %edi, 4)
	movl $138, %edi
	movl (%esi, %edi, 4), %eax
	movl $131, %edi
	movl %eax, (%esi, %edi, 4)
	movl $139, %edi
	movl $5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $131, %edi
	movl (%esi, %edi, 4), %eax
	movl $139, %edi
	movl (%esi, %edi, 4), %ebx
	movl $0, %edx
	divl %ebx
	movl $140, %edi
	movl %eax, (%esi, %edi, 4)
	movl $140, %edi
	movl (%esi, %edi, 4), %eax
	movl $132, %edi
	movl %eax, (%esi, %edi, 4)

	.global _Function.funcTest
_Function.funcTest:
	pushl %ebp
	movl %esp, %ebp
	movl $141, %edi
	leal _STRING9, %eax
	movl %eax, (%esi, %edi, 4)
	movl $141, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintString
	movl 8(%ebp), %eax
	movl $8, %edi
	movl %eax, (%esi, %edi, 4)
	movl $8, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $8, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	call _PrintInt
	movl 8(%ebp), %eax
	movl $8, %edi
	movl %eax, (%esi, %edi, 4)
	movl $8, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret
	movl $8, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)

	.global _Function.errorRetType
_Function.errorRetType:
	pushl %ebp
	movl %esp, %ebp
	movl $142, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $142, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global _Statement.stmt2
_Statement.stmt2:
	pushl %ebp
	movl %esp, %ebp
_L23:
	movl $144, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $144, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setg %al
	movzbl %al, %eax
	movl $145, %edi
	movl %eax, (%esi, %edi, 4)
	movl $145, %edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je _L24
	movl $147, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $147, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $148, %edi
	movl %eax, (%esi, %edi, 4)
	movl $148, %edi
	movl (%esi, %edi, 4), %eax
	movl $143, %edi
	movl %eax, (%esi, %edi, 4)
	movl $149, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $149, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $150, %edi
	movl %eax, (%esi, %edi, 4)
	movl $150, %edi
	movl (%esi, %edi, 4), %eax
	movl $146, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L23
_L24:
_L25:
	movl $151, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $151, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setl %al
	movzbl %al, %eax
	movl $152, %edi
	movl %eax, (%esi, %edi, 4)
	movl $152, %edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je _L26
	movl $154, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $153, %edi
	movl (%esi, %edi, 4), %eax
	movl $154, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $155, %edi
	movl %eax, (%esi, %edi, 4)
	movl $155, %edi
	movl (%esi, %edi, 4), %eax
	movl $153, %edi
	movl %eax, (%esi, %edi, 4)
	movl $156, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $156, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $157, %edi
	movl %eax, (%esi, %edi, 4)
	movl $157, %edi
	movl (%esi, %edi, 4), %eax
	movl $143, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L25
_L26:
	movl $158, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $158, %edi
	movl (%esi, %edi, 4), %eax
	movl $143, %edi
	movl %eax, (%esi, %edi, 4)
	jmp _L27
_L28:
	movl $159, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $159, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $160, %edi
	movl %eax, (%esi, %edi, 4)
	movl $160, %edi
	movl (%esi, %edi, 4), %eax
	movl $143, %edi
	movl %eax, (%esi, %edi, 4)
_L27:
	movl $161, %edi
	movl $10, %eax
	movl %eax, (%esi, %edi, 4)
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	movl $161, %edi
	movl (%esi, %edi, 4), %ebx
	cmpl %ebx, %eax
	setl %al
	movzbl %al, %eax
	movl $162, %edi
	movl %eax, (%esi, %edi, 4)
	movl $162, %edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je _L29
	movl $143, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call _PrintInt
	jmp _L28
_L29:

	.global _Variable.varTest
_Variable.varTest:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl $12, %edi
	movl %eax, (%esi, %edi, 4)
	movl $12, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $163, %edi
	movl %eax, (%esi, %edi, 4)
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $164, %edi
	movl $5, %eax
	movl %eax, (%esi, %edi, 4)
	movl $165, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $165, %edi
	movl (%esi, %edi, 4), %eax
	movl $164, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $166, %edi
	movl %eax, (%esi, %edi, 4)
	movl $165, %edi
	movl (%esi, %edi, 4), %eax
	movl $166, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $167, %edi
	movl %eax, (%esi, %edi, 4)
	movl $167, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	call malloc
	movl $168, %edi
	movl %eax, (%esi, %edi, 4)
	movl $164, %edi
	movl (%esi, %edi, 4), %eax
	movl $168, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	movl $169, %edi
	movl $0, %eax
	movl %eax, (%esi, %edi, 4)
	movl $168, %edi
	movl (%esi, %edi, 4), %eax
	movl $167, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $168, %edi
	movl %eax, (%esi, %edi, 4)
_L30:
	movl $167, %edi
	movl (%esi, %edi, 4), %eax
	movl $165, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $167, %edi
	movl %eax, (%esi, %edi, 4)
	movl $167, %edi
	movl (%esi, %edi, 4), %eax
	testl %eax, %eax
	je _L31
	movl $168, %edi
	movl (%esi, %edi, 4), %eax
	movl $165, %edi
	movl (%esi, %edi, 4), %ebx
	subl %ebx, %eax
	movl $168, %edi
	movl %eax, (%esi, %edi, 4)
	movl $169, %edi
	movl (%esi, %edi, 4), %eax
	movl $168, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 0(%ebx)
	jmp _L30
_L31:
	movl 8(%ebp), %eax
	movl $12, %edi
	movl %eax, (%esi, %edi, 4)
	movl $168, %edi
	movl (%esi, %edi, 4), %eax
	movl $12, %edi
	movl (%esi, %edi, 4), %ebx
	movl %eax, 4(%ebx)
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl 8(%ebp), %eax
	movl $12, %edi
	movl %eax, (%esi, %edi, 4)
	movl $12, %edi
	movl (%esi, %edi, 4), %ebx
	movl 4(%ebx), %eax
	movl $170, %edi
	movl %eax, (%esi, %edi, 4)
	movl $12, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, 8(%ebp)
	movl $171, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $172, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $171, %edi
	movl (%esi, %edi, 4), %eax
	movl $172, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $173, %edi
	movl %eax, (%esi, %edi, 4)
	movl $170, %edi
	movl (%esi, %edi, 4), %eax
	movl $173, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $174, %edi
	movl %eax, (%esi, %edi, 4)
	movl $174, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $175, %edi
	movl %eax, (%esi, %edi, 4)
	movl $176, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $177, %edi
	movl $4, %eax
	movl %eax, (%esi, %edi, 4)
	movl $176, %edi
	movl (%esi, %edi, 4), %eax
	movl $177, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $178, %edi
	movl %eax, (%esi, %edi, 4)
	movl $175, %edi
	movl (%esi, %edi, 4), %eax
	movl $178, %edi
	movl (%esi, %edi, 4), %ebx
	addl %ebx, %eax
	movl $179, %edi
	movl %eax, (%esi, %edi, 4)
	movl $179, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $180, %edi
	movl %eax, (%esi, %edi, 4)
	movl $180, %edi
	movl (%esi, %edi, 4), %eax
	leave
	ret

	.global main
main:
	pushl %ebp
	movl %esp, %ebp
	pushl $4000       # 4000/4 = 1000 fake registers
	call malloc
	movl %eax, %esi   # store registers base into %esi
	movl $182, %edi
	movl $1, %eax
	movl %eax, (%esi, %edi, 4)
	movl $182, %edi
	movl (%esi, %edi, 4), %eax
	movl $181, %edi
	movl %eax, (%esi, %edi, 4)
	call _Mac_New
	movl $184, %edi
	movl %eax, (%esi, %edi, 4)
	movl $184, %edi
	movl (%esi, %edi, 4), %eax
	movl $183, %edi
	movl %eax, (%esi, %edi, 4)
	movl $185, %edi
	movl $2, %eax
	movl %eax, (%esi, %edi, 4)
	movl $185, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $183, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $183, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $186, %edi
	movl %eax, (%esi, %edi, 4)
	movl $186, %edi
	movl (%esi, %edi, 4), %ebx
	movl 8(%ebx), %eax
	movl $187, %edi
	movl %eax, (%esi, %edi, 4)
	movl $187, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, %edi
	call *%edi
	movl $188, %edi
	movl %eax, (%esi, %edi, 4)
	movl $183, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $183, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $189, %edi
	movl %eax, (%esi, %edi, 4)
	movl $189, %edi
	movl (%esi, %edi, 4), %ebx
	movl 12(%ebx), %eax
	movl $190, %edi
	movl %eax, (%esi, %edi, 4)
	movl $190, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, %edi
	call *%edi
	call _Function_New
	movl $192, %edi
	movl %eax, (%esi, %edi, 4)
	movl $192, %edi
	movl (%esi, %edi, 4), %eax
	movl $191, %edi
	movl %eax, (%esi, %edi, 4)
	movl $193, %edi
	movl $3, %eax
	movl %eax, (%esi, %edi, 4)
	movl $181, %edi
	movl (%esi, %edi, 4), %eax
	movl $193, %edi
	movl (%esi, %edi, 4), %ebx
	imull %ebx, %eax
	movl $194, %edi
	movl %eax, (%esi, %edi, 4)
	movl $194, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $191, %edi
	movl (%esi, %edi, 4), %eax
	pushl %eax
	movl $191, %edi
	movl (%esi, %edi, 4), %ebx
	movl 0(%ebx), %eax
	movl $195, %edi
	movl %eax, (%esi, %edi, 4)
	movl $195, %edi
	movl (%esi, %edi, 4), %ebx
	movl 12(%ebx), %eax
	movl $196, %edi
	movl %eax, (%esi, %edi, 4)
	movl $196, %edi
	movl (%esi, %edi, 4), %eax
	movl %eax, %edi
	call *%edi
	movl $197, %edi
	movl %eax, (%esi, %edi, 4)
	leave
	pushl $0
	call exit


	.data
_STRING0:
	.string "Computer"
_STRING3:
	.string "Expression"
_STRING9:
	.string "FuncTest:"
_STRING4:
	.string "Function"
_STRING8:
	.string "Hello Mac!"
_STRING1:
	.string "Mac"
_STRING7:
	.string "Main"
_STRING2:
	.string "OSX"
_STRING5:
	.string "Statement"
_STRING6:
	.string "Variable"
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
