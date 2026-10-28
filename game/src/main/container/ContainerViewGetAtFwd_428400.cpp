/* rgp:protos */
#line 1
#include "types.h"

/* Pool accessor of the func_0040A290_e2 / ContainerViewGetAtFwd_3f9af0 family.
   2 x 4-word virtual tail-call thunk (vtable slot 0x10 = index 2),
   then the accessor.  The STRIDE is read off this member's OWN listing:
   sll 2, addu, sll 1, addu, sll 3 -> ((((i<<2)+i)<<1)+i)<<3 = 88 */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class Vfunc_00428400 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_428400(Vfunc_00428400 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void __attribute__((naked)) func_00428400_e1(Vfunc_00428400 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void *func_00428400_e2(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 88) : (void *)0;
}
