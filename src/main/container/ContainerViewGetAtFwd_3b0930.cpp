#include "types.h"

/* ONE symbol, 3 entry points.  `lw $25,0x0($4)` / `lw $25,K($25)` /
   `jr $25` is a C++ VIRTUAL tail call: slot K = 4*index + 8.  All the
   entries must come out of ONE translation unit, in listing order --
   mwcc gives each its own .text and the lcf takes them in file order. */

class V3B0930_0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

class V3B0930_1 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void ContainerViewGetAtFwd_3b0930(V3B0930_0 *o)
{
    o->v2();
}

extern "C" void func_003B0930_e1(V3B0930_1 *o)
{
    o->v2();
}

extern "C" s32 func_003B0930_e2(void)
{
    return 0;
}


