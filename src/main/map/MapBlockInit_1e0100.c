#include "types.h"

extern void MapDataInit_1e7c50(s32);
extern void MapBlockBoxListInit_1e0580(s32);
extern void AreaBoxInit_1e01f0(s32);
extern void MapDataSetType_1e7430(s32, s32);
extern void MapBlockClearLoadState_1e00c0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapBlockInit_1e0100(s32 p0)
{
    MapDataInit_1e7c50(p0);
    MapBlockBoxListInit_1e0580((p0 + 0x54));
    AreaBoxInit_1e01f0((p0 + 0x74));
    MapDataSetType_1e7430(p0, 4);
    MapBlockClearLoadState_1e00c0(p0);
}
