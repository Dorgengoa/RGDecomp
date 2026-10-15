#include "types.h"

/* UnitBaseIsPlayerCharaThunk_3a3610 -- shape-identical to merged EffTexUvRandParamApply_19a540 (24 B).
   ONE symbol, TWO entry points: a 4-word virtual tail-call thunk then a
   2-word `return 0` with no symbol of its own.  mwcc gives each function its
   own `.text` and the two sizes SUM to retail's 0x18.
   Vtable slot 0x44 == 4 * (15 + 2), so virtual index 15.
   NOTE: the slot lives in the CLASS, not in a constant -- this file is hand
   derived because a textual immediate substitution would have edited only
   the comment. */

class Vfunc_003A3610 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
};

extern "C" void UnitBaseIsPlayerCharaThunk_3a3610(Vfunc_003A3610 *o)
{
    o->v15();
}

extern "C" s32 func_003A3610_e1(void)
{
    return 0;
}
