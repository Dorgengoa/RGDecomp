#include "types.h"

extern s32 GetReadBuffHeap_2025e0(void);
extern void WarpMenuLoad_39de60(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapMgrWarpMenuLoad_1e2f60(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;

    r0 = GetReadBuffHeap_2025e0();
    WarpMenuLoad_39de60((p0 + 0x18B0), p1, p2, r0, p3);
}
