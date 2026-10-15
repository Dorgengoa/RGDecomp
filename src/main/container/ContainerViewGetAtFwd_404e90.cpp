#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

class Vfunc_00404E90 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void ContainerViewGetAtFwd_404e90(Vfunc_00404E90 *o)
{
    o->v2();
}

extern "C" void func_00404E90_e1(Vfunc_00404E90 *o)
{
    o->v2();
}

extern "C" void func_00404E90_e2(Vfunc_00404E90 *o)
{
    o->v2();
}

extern "C" void *func_00404E90_e3(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 32) : (void *)0;
}
