    .data
int_format:
	.string "%d\n"
regs:
    .int 0

    .text
    .global main
main:
    pushl %ebp
    movl %esp, %ebp

    pushl $4000                 # 4000/4 = 1000 fake registers
    call malloc
    movl %eax, regs
    mov regs, %esi              # store registers base into %esi

    mov $2, %edi                # temp id
    movl (%esi, %edi, 4), %eax  # reg[id] => eax

    pushl %eax
    call printi
    leave
    pushl $0
    call exit

	.globl printi
printi:
	push	%ebp
	movl	%esp, %ebp
	pushl	8(%ebp)
	pushl	$int_format
	call	printf
	leave
	ret
