#include "types.h"

extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrRemoveById_2e9df0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventObjMgrRemoveByIdFwd_2fd970(s32 p0)
{
    s32 r0;

    r0 = GetEventObjMgr_2d1960();
    EventObjMgrRemoveById_2e9df0(r0, p0);
}
