#include "types.h"

extern void HudFadeOutAll_2f47e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
    u8 pad01C[0x8];
    u8 m24;
};

void MapCaptionShow_33f940(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m18;
    if (t0 != 2) {
        if (t0 != 1) {
            return;
        }
        p0->m24 = 1;
    } else {
        p0->m18 = 4;
        HudFadeOutAll_2f47e0(0xF, t0);
    }
}
