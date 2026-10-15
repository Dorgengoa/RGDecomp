#include "types.h"

extern void EventVolumeRecSetCount_2e4d70(void *, s32);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrAddVolumeRec_2ea190(s32, s32, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;
extern s32 D_00482834;
extern u8 D_004E66D0[];

s32 EvScriptCmdVolumeRecRegister_3015c0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 t0;
    s32 r1;
    s32 t1;
    s32 t2;
    s32 r2;

    rv3 = 1;
    if (p1 != 0) {
        rv3 = 0;
    } else {
        t0 = D_00482834;
        EventVolumeRecSetCount_2e4d70(D_004E66D0, t0);
        r1 = GetEventObjMgr_2d1960();
        t1 = D_0047F0C0;
        t2 = D_0047F0C4;
        r2 = EventObjMgrAddVolumeRec_2ea190(r1, t1, t2, D_004E66D0);
        rv3 = 1;
    }
    return rv3;
}
