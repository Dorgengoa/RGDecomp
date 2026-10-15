#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x58B0];
    u8 m58B0;
};

void GameSceneSetCBlurEnable_1cf7e0(struct Obj0 *p0, s32 p1)
{
    if (p1 != 0) {
        p0->m58B0 = 1;
    } else {
        p0->m58B0 = 0;
    }
}
