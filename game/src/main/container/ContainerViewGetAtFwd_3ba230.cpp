/* rgp:protos */
#line 1
#include "types.h"

/* clone of func_0040A290_e2 family (see src/s23c/ContainerViewGetAtFwd_40a290.cpp).
   ONE symbol, TWO entries: 4-word virtual tail-call thunk (vtable slot
   0x10, index 2) then the pool accessor.  Stride read off this member's
   OWN listing: sll $3, $5, 1 -> 2. */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class V003BA230 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_3ba230(V003BA230 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void *func_003BA230_e1(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 2) : (void *)0;
}
