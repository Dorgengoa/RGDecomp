#include "types.h"

extern s32 EvObjResolveTarget_2f9a60(s32, s32);
extern s32 TargetRefResolve_2e5ed0(s32, s32);
extern s32 EvSwitchObjApplyState_2f8240(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvSwitchObjResolve_2f8360(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv5;
    s32 r2;
    s32 rv4;
    s32 r3;

    r0 = EvObjResolveTarget_2f9a60(p0, 0);
    r1 = TargetRefResolve_2e5ed0((p0 + 0xA0), 0);
    rv5 = rv4;
    if (r1 == 0) {
        rv5 = 0;
    } else {
        r2 = TargetRefResolve_2e5ed0((p0 + 0xE0), 0);
        rv4 = 1;
        if (r2 == 0) {
            rv4 = 0;
        } else {
            r3 = EvSwitchObjApplyState_2f8240(p0);
            rv4 = 1;
        }
        rv5 = rv4;
    }
    return rv5;
}
