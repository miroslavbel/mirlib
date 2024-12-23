.extern _c_start

.globl _start

.text

/*
 * \brief Simple `start` routine.
 *
 * \warning After `_c_start` function finishes, it immediately syscalls `exit`
 * with the result of `_c_start` function without any additional actions (e.g.
 * crt requires to call functions passed to `atexit` before terminating the
 * process).
 *
 * /see [AMD64 ABI Draft 0.99.6](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)
 * 3.4 Process Initialization
 */
_start:
    // 1. "the user code should mark the deepest stack frame by setting the
    //    frame pointer to zero"
    xor %rbp, %rbp

    // 2. setting `_c_start` params. Ignoring auxiliary vector
    // 2.1 argc, argv
    pop %rdi         // argc -> %rdi
    mov %rsp, %rsi   // argv -> %rsi

    // 2.2 envp
    // NOTE: calculating 8+8*argc+%rsp in %rax
    mov %rdi, %rax   // argc      -> %rax
    mov   $8, %rdx   // $8        -> %rdx
    mul %rdx         // %rdx:%rax := %rax * %rdx
    add %rsp, %rax   // %rax      := %rax + %rsp
    add   $8, %rax   // %rax      += $8

    // finally setting envp as the third param
    mov %rax, %rdx   // envp -> %rdx

    // 3. aligning the stack back
    /* NOTE: %rsp needs to be 16-byte aligned and it'is guaranteed to be so at
     *       process entry. But as we already have poped %rdi (8 bytes) we need
     *       to align it again.                                               */
    and $-16, %rsp

    // 4. calling the _c_start
    call _c_start

    // syscalling exit
    mov %rax, %rdi   // arg1 := result of _c_start
    mov  $60, %rax   // sysno. See `<asm/unistd.h>`
    syscall
