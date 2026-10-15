#include "types.h"

extern void MapDataInit_1e7c50(s32);
extern void Nop_1ed0b0(s32);
extern void MapBlockBoxListInit_1e0580(s32);
extern void Nop_1ed090(s32);
extern void AreaBoxInit_1e01f0(s32);
extern s32 MapBlockInit_1e0100(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapBlockCtor_1dd920(s32 p0)
{
    s32 r5;

    MapDataInit_1e7c50(p0);
    Nop_1ed0b0((p0 + 0x54));
    MapBlockBoxListInit_1e0580((p0 + 0x54));
    Nop_1ed090((p0 + 0x74));
    AreaBoxInit_1e01f0((p0 + 0x74));
    r5 = MapBlockInit_1e0100(p0);
    return p0;
}
