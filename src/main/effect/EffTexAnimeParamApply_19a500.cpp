#include "types.h"

/* ONE symbol, 2 entry points.  `lw $25,0x0($4)` / `lw $25,K($25)` /
   `jr $25` is a C++ VIRTUAL tail call: slot K = 4*index + 8.  All the
   entries must come out of ONE translation unit, in listing order --
   mwcc gives each its own .text and the lcf takes them in file order. */

class V19A500_0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void EffTexAnimeParamApply_19a500(V19A500_0 *o)
{
    o->v2();
}

extern "C" void func_0019A500_e1(void)
{
}


