#include "types.h"

extern void AngleWrap_1cbf30(f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    u8 m18;
    u8 pad019[0x1B];
    f32 m34;
};

void NpcCfgLocalToWorldYaw_2fd890(struct Obj0 *p0, f32 fa0)
{
    u8 t0;
    f32 t1;

    t0 = p0->m18;
    if ((t0 & 1) != 0) {
        t1 = p0->m34;
        AngleWrap_1cbf30((fa0 + t1));
    } else {
        AngleWrap_1cbf30(fa0);
    }
}
