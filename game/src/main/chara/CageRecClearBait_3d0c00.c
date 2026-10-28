/* rgp:protos */
#define RGP_SELF_CageRecClearBait_3d0c00 1
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
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x2];
    s16 m02;
    u8 pad004[0x7E8];
    f32 m7EC;
};

s32 CageRecClearBait_3d0c00(struct Obj0 *p0)
{
    struct Obj1 * t0;
    struct Obj1 * t1;
    f32 t2;

    t0 = p0->m18;
    p0->m18->m02 = -1;
    t1 = p0->m18;
    t2 = p0->m18->m7EC;
    if (t2 > 0.0f) {
        p0->m18->m7EC = 0.0f;
    }
    return 1;
}
