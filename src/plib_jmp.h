#ifndef JMP_H
#define JMP_H

struct plib_jmp_buf {
    void *rsp;
    void *rip;
    long rbx, rbp, r12, r13, r14, r15;
};

int plib_setjmp(struct plib_jmp_buf *buf);
[[noreturn]] void plib_longjmp(struct plib_jmp_buf *buf, int val);

#endif

