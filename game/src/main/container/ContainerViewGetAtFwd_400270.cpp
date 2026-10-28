/* rgp:protos */
#line 1
#include "types.h"

/* Pool accessor of the func_0040A290_e2 / ContainerViewGetAtFwd_3f9af0 family.
   2 x 4-word virtual tail-call thunk (vtable slot 0x10 = index 2),
   then the accessor.  The STRIDE is read off this member's OWN listing:
   sll 3 alone -> 8 */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class Vfunc_00400270 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_400270(Vfunc_00400270 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void __attribute__((naked)) func_00400270_e1(Vfunc_00400270 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" void *func_00400270_e2(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 8) : (void *)0;
}
