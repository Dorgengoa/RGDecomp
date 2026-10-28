/* rgp:protos */
#define RGP_SELF_UiPanelSetOffset_33d560 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x58];
    f32 m58;
    f32 m5C;
};

f32 UiPanelSetOffset_33d560(struct Obj0 *p0, s32 p1, s32 p2)
{
    p0->m58 = ((f32)p1);
    p0->m5C = ((f32)p2);
    return ((f32)p2);
}
