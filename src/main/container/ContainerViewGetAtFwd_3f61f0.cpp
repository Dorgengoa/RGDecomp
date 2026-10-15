#include "types.h"

/* Pool accessor of the func_0040A290_e2 / ContainerViewGetAtFwd_3f9af0 family.
   1 x 4-word virtual tail-call thunk (vtable slot 0x10 = index 2),
   then the accessor.  The STRIDE is read off this member's OWN listing:
   sll 3, subu, sll 2 -> ((i<<3)-i)<<2 = 28 */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class Vfunc_003F61F0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void ContainerViewGetAtFwd_3f61f0(Vfunc_003F61F0 *o)
{
    o->v2();
}

extern "C" void *func_003F61F0_e1(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 28) : (void *)0;
}
