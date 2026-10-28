/* rgp:protos */
#define RGP_SELF_EvSubNodeSetMotionBlendSpeed_252570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004BDDB0[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20];
    f32 m20;
};

struct Obj1 {
    u8 pad000[0x60];
    s32 m60;
};

s32 EvSubNodeSetMotionBlendSpeed_252570(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 r;

    r = EventCastSetMotionBlendSpeed_258250(D_004BDDB0, p1->m60, p0->m20);
    return 0;
}
