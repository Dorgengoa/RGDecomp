#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern void MapMgrCaptionDraw_1e2620(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawCaption_1ffb00(void)
{
    s32 r0;

    r0 = GetMapMgr_201a90();
    MapMgrCaptionDraw_1e2620(r0);
}
