#include "types.h"

extern void EvObjLiftSetTargetPairCount_336090(void *, s32);
extern void EvObjLiftSetTargetSetCount_336010(void *, s32);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrCreateLift_2e9fb0(s32, s32, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;
extern s32 D_00482884;
extern s32 D_0048288C;
extern u8 D_004E7000[];

s32 EvScriptCmdObjLiftRegister_2feaf0(s32 p0, s32 p1)
{
    s32 rv4;
    s32 t0;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 t3;
    s32 r3;

    rv4 = 1;
    if (p1 != 0) {
        rv4 = 0;
    } else {
        t0 = D_00482884;
        EvObjLiftSetTargetPairCount_336090(D_004E7000, t0);
        t1 = D_0048288C;
        EvObjLiftSetTargetSetCount_336010(D_004E7000, t1);
        r2 = GetEventObjMgr_2d1960();
        t2 = D_0047F0C0;
        t3 = D_0047F0C4;
        r3 = EventObjMgrCreateLift_2e9fb0(r2, t2, t3, D_004E7000);
        rv4 = 1;
    }
    return rv4;
}
