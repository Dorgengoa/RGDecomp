#include "types.h"

extern s32 GetReadBuffHeap_2025e0(void);
extern void MapCaptionLoad_33fa90(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapMgrCaptionLoad_1e2f10(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = GetReadBuffHeap_2025e0();
    MapCaptionLoad_33fa90((p0 + 0x18E8), p1, r0, p2);
}
