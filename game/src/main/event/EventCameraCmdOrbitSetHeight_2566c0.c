/* rgp:protos */
#define RGP_SELF_EventCameraCmdOrbitSetHeight_2566c0 1
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
    u8 pad000[0x30];
    f32 m30;
};

struct Obj1 {
    u8 pad000[0x54];
    f32 m54;
    u8 pad058[0xC];
    f32 m64;
    u8 pad068[0xC];
    f32 m74;
};

s32 EventCameraCmdOrbitSetHeight_2566c0(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m54 = (p0->m30 + p1->m64);
    p1->m74 = p0->m30;
    return 0;
}
