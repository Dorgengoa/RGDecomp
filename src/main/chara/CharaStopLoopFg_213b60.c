#include "types.h"

extern void GetCurrentScene_1f5be0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA5C];
    s16 mA5C;
    s16 mA5E;
};

void CharaStopLoopFg_213b60(struct Obj0 *p0)
{
    GetCurrentScene_1f5be0();
    p0->mA5C = -1;
    p0->mA5E = -1;
}
