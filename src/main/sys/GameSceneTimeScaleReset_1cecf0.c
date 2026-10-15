#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5E00];
    u8 m5E00;
    u8 pad5E01[0x3];
    s32 m5E04;
    s32 m5E08;
    s32 m5E0C;
    s32 m5E10;
    u8 m5E14;
    u8 m5E15;
};

void GameSceneTimeScaleReset_1cecf0(struct Obj0 *p0)
{
    p0->m5E0C = 0x3F800000;
    p0->m5E00 = 0;
    p0->m5E14 = 0;
    p0->m5E08 = 0x3F800000;
    p0->m5E04 = 1;
    p0->m5E10 = -1;
    p0->m5E15 = 0;
}
