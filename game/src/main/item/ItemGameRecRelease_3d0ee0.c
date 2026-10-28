/* rgp:protos */
#define RGP_SELF_ItemGameRecRelease_3d0ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj1 * D_004838F0;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x14];
    s16 m14;
    u8 pad016[0x2];
    s32 m18;
};

struct Obj1 {
    u8 pad000[0x174];
    s32 m174;
};

s32 ItemGameRecRelease_3d0ee0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv1;
    s16 t1;
    s32 t2;
    s32 r0;

    t0 = D_004838F0;
    rv1 = 1;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        t1 = p0->m14;
        t2 = D_004838F0->m174;
        r0 = GameRecReleaseCageSlot_3ce140(t2, t1);
        p0->m14 = -1;
        p0->m18 = 0;
        rv1 = 1;
    }
    return rv1;
}
