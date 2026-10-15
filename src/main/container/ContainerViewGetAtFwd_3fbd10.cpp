#include "types.h"

/* Pool accessor of the func_0040A290_e2 / ContainerViewGetAtFwd_3f9af0 family.
   4 x 4-word virtual tail-call thunk (vtable slot 0x10 = index 2),
   then the accessor.  The STRIDE is read off this member's OWN listing:
   sll 2, addu, sll 2 -> ((i<<2)+i)<<2 = 20 */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class Vfunc_003FBD10 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void ContainerViewGetAtFwd_3fbd10(Vfunc_003FBD10 *o)
{
    o->v2();
}

extern "C" void func_003FBD10_e1(Vfunc_003FBD10 *o)
{
    o->v2();
}

extern "C" void func_003FBD10_e2(Vfunc_003FBD10 *o)
{
    o->v2();
}

extern "C" void func_003FBD10_e3(Vfunc_003FBD10 *o)
{
    o->v2();
}

extern "C" void *func_003FBD10_e4(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 20) : (void *)0;
}
