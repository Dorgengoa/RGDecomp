#include "types.h"

struct C400 {
    u8 pad000[0x190];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
};

extern "C" s32 ScriptSlotGetInt_3348b0(s32);
extern "C" s32 MotionListResetAll_171e00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004826E0;

extern "C" s32 ScriptCmdCurObjResetMotions_331da0(s32 p0, s32 p1)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 rv3;
    s32 r2;

    if (p1 != 1) {
        return 0;
    }
    r0 = ScriptSlotGetInt_3348b0(p0);
    t0 = D_004826E0;
    if (t0 != 0) {
        r1 = ((struct C400 *)t0)->v4();
        rv3 = 0;
        if (r1 != 0) {
            r2 = MotionListResetAll_171e00((r1 + 0x1F0));
            rv3 = r2;
        }
    }
    return 1;
}
