    .data
    .align 4
  	.section	.rodata
  format: .string	"%li\n"
  	.text
  	.globl	main
  main:
  	endbr64
  	push	%rbp
    mov $3,%rax
    push %rax
    mov $2,%rax
    push %rax
    pop %rax
    pop %rbx
    sub %rbx,%rax
    push %rax
    mov $4,%rax
    push %rax
    mov $2,%rax
    push %rax
    pop %rax
    pop %rbx
    add %rbx,%rax
    push %rax
    pop %rax
    pop %rbx
    mul %rbx
    push %rax
    pop  %rax
    mov	%rax, %rsi
    lea	format(%rip), %rax
    mov	%rax, %rdi
    mov	$0, %rax
    call	printf@PLT
    mov	$0, %rax
    pop	%rbp
    ret
    .section	.note.GNU-stack,"",@progbits
