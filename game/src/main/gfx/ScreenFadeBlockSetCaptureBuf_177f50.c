/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockSetCaptureBuf_177f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x2C];
    struct Obj1 *m2C;
};

struct Obj1 {
    u8 pad000[0x50];
    s32 m50;
};

void ScreenFadeBlockSetCaptureBuf_177f50(struct Obj0 *p0, s32 p1)
{
    if (p0->m2C != 0) {
        p0->m2C->m50 = p1;
    }
}
