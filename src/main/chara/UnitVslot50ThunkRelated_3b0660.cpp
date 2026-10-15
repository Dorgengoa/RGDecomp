#include "types.h"

/* UnitVslot50ThunkRelated_3b0660 -- shape-identical to merged EffTexUvRandParamApply_19a540 (24 B).
   ONE symbol, TWO entry points: a 4-word virtual tail-call thunk then a
   2-word `return 0` with no symbol of its own.  mwcc gives each function its
   own `.text` and the two sizes SUM to retail's 0x18.
   Vtable slot 0x54 == 4 * (19 + 2), so virtual index 19.
   NOTE: the slot lives in the CLASS, not in a constant -- this file is hand
   derived because a textual immediate substitution would have edited only
   the comment. */

class Vfunc_003B0660 {
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
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
};

extern "C" void UnitVslot50ThunkRelated_3b0660(Vfunc_003B0660 *o)
{
    o->v19();
}

extern "C" s32 func_003B0660_e1(void)
{
    return 0;
}
