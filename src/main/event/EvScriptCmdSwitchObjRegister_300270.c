#include "types.h"

extern s32 EventRecGetKey_2e5730(void *);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrCreateSwitchObj_2ea090(s32, s32, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;
extern u8 D_004E6720[];

s32 EvScriptCmdSwitchObjRegister_300270(void)
{
    s32 r0;
    s32 r1;
    s32 t0;
    s32 t1;
    s32 r2;

    r0 = EventRecGetKey_2e5730(D_004E6720);
    if (r0 == 0) {
        return 1;
    }
    r1 = GetEventObjMgr_2d1960();
    t0 = D_0047F0C0;
    t1 = D_0047F0C4;
    r2 = EventObjMgrCreateSwitchObj_2ea090(r1, t0, t1, D_004E6720);
    return 1;
}
