#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x12];
    s16 m12;
};

void OptionsSetSoundOutput_3d6160(struct Obj0 *p0, s32 p1)
{
    if (p1 == 1) {
        p0->m12 = 1;
    } else {
        p0->m12 = 0;
    }
}
