#include "types.h"

extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrCreateFollowObj_2ea070(s32, s32, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;
extern u8 D_004E6880[];

s32 EvScriptCmdFollowObjRegister_2fffd0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetEventObjMgr_2d1960();
    r1 = EventObjMgrCreateFollowObj_2ea070(r0, D_0047F0C0, D_0047F0C4, D_004E6880);
    return 1;
}
