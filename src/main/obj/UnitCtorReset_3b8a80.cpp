#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
};

extern "C" void UnitBaseResetIdsAndClear_3b8a60(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" void UnitCtorReset_3b8a80(s32 p0)
{
    UnitBaseResetIdsAndClear_3b8a60(p0);
    ((struct C0 *)p0)->v8();
}
