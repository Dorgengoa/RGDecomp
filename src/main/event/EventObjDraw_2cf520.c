#include "types.h"

extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrDrawAll_2e8210(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventObjDraw_2cf520(void)
{
    s32 r0;

    r0 = GetEventObjMgr_2d1960();
    EventObjMgrDrawAll_2e8210(r0);
}
