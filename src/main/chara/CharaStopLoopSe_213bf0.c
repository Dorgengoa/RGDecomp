#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3F4];
    s32 m3F4;
    u8 pad3F8[0x660];
    s16 mA58;
    s16 mA5A;
};

void CharaStopLoopSe_213bf0(struct Obj0 *p0)
{
    if (p0->m3F4 != 0) {
        p0->mA58 = -1;
        p0->mA5A = -1;
    }
}
