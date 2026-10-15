#include "types.h"

extern s32 SoundPlayDefault_1b9ae0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
};

s32 EvSubNodePlaySound_252160(struct Obj0 *p0)
{
    s32 r;

    r = SoundPlayDefault_1b9ae0(p0->m20, p0->m24, 0);
    return 0;
}
