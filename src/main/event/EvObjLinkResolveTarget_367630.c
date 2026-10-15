#include "types.h"

extern s32 TargetRefResolve_2e5ed0(s32, s32);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EvObjLinkGetKey_3676f0(s32);
extern s32 EvMapObjFindByName_2e9880(s32, s32);
extern s32 EvObjGetTargetRef_2f9ca0(s32);
extern s32 TargetRefGetId_2e7120(s32);
extern s32 TargetRefGetName_2e70f0(s32);
extern s32 TargetRefSetMapObj_2e6470(s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvObjLinkResolveTarget_367630(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv9;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 rv8;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;

    r0 = TargetRefResolve_2e5ed0((p0 + 0xA0), p1);
    rv9 = rv8;
    if (r0 == 0) {
        rv9 = 0;
    } else {
        r1 = GetEventObjMgr_2d1960();
        r2 = EvObjLinkGetKey_3676f0(p0);
        r3 = EvMapObjFindByName_2e9880(r1, r2);
        rv8 = 1;
        if (r3 == 0) {
            rv8 = 0;
        } else {
            r4 = EvObjGetTargetRef_2f9ca0(r3);
            r5 = TargetRefGetId_2e7120((p0 + 0xA0));
            r6 = TargetRefGetName_2e70f0((p0 + 0xA0));
            r7 = TargetRefSetMapObj_2e6470(r4, r5, r6, 0.0f);
            rv8 = 1;
        }
        rv9 = rv8;
    }
    return rv9;
}
