#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB4C];
    s16 mB4C;
    s16 mB4E;
    s16 mB50;
    s16 mB52;
};

void CharaRequestBattleEnter_213ec0(struct Obj0 *p0, s32 p1)
{
    if (p1 != 0) {
        p0->mB4C = 1;
        p0->mB4E = 0;
    } else {
        p0->mB4C = 2;
        p0->mB4E = 0;
    }
    p0->mB50 = 0;
    p0->mB52 = 0;
}
