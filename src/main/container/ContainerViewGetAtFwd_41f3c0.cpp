#include "types.h"

/* Head of a 4-member byte-identical group (96 B each):
   ContainerViewGetAtFwd_41f3c0 / ContainerViewGetAtFwd_40b030 / ContainerViewGetAtFwd_41d950 / ContainerViewGetAtFwd_420e50.

   ONE symbol, THREE entry points: two IDENTICAL 4-word virtual tail-call
   thunks (vtable slot 0x10, index 2) and then the pool accessor at +0x20.
   ⚠ The third entry carries an `alabel func_0040A2B0` that main_data
   (.word, two vtable slots) and DataTableViewGetAtThunk_40a440 (`j`) both reference by NAME.
   Compiling this unit removes the assembly definition; scripts/link.py's
   cross_part_symbols() emits `func_0040A2B0 = 0x0040A2B0;` into the lcf
   because the address is derivable from the name, and REFUSES the link if it
   ever is not -- so the failure mode is loud, not silent. */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class V40A290 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void ContainerViewGetAtFwd_41f3c0(V40A290 *o)
{
    o->v2();
}

extern "C" void func_0041F3C0_e1(V40A290 *o)
{
    o->v2();
}

extern "C" void *func_0041F3C0_e2(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 20) : (void *)0;
}
