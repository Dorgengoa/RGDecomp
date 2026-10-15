#include "types.h"

extern s32 GetTargetMng_313dd0(void);
extern s32 TargetMngCycleLockOn_31f510(s32, s32);
extern s32 TargetMngGetTargetRef_320820(s32);
extern s32 TargetMngSetTarget_313ad0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TargetMngCycleAndSetTarget_313a10(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv4;
    s32 r2;
    s32 r3;

    r0 = GetTargetMng_313dd0();
    r1 = TargetMngCycleLockOn_31f510(r0, p0);
    rv4 = r1;
    if (r1 >= 0) {
        r2 = TargetMngGetTargetRef_320820(r0);
        r3 = TargetMngSetTarget_313ad0(r2);
        rv4 = r3;
    }
    return rv4;
}
