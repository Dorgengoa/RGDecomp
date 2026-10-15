#include "types.h"

extern s32 ScriptArgGetStr_1c2bb0(s32);
extern s32 VariantGetInt_1c2bd0(s32);
extern s32 Nop_207fd0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SysCfgDebugCheckCmd_1c2a40(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 != 2) {
        rv3 = 0;
    } else {
        r0 = ScriptArgGetStr_1c2bb0(p0);
        r1 = VariantGetInt_1c2bd0((p0 + 8));
        r2 = Nop_207fd0(r0, (r1 != 0));
        rv3 = 1;
    }
    return rv3;
}
