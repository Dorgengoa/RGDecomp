#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0x2];
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
};

void SkillTimerReset_3e3d20(struct Obj0 *p0)
{
    p0->m00 = -1;
    p0->m02 = -1;
    p0->m04 = -1;
    p0->m08 = 0;
    p0->m0C = 0xBF800000;
    p0->m10 = 0xBF800000;
    p0->m14 = 0xBF800000;
}
