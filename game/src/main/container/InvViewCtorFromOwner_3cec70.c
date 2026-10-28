/* rgp:protos */
#define RGP_SELF_InvViewCtorFromOwner_3cec70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_00475890[];
extern u8 D_004758B0[];

struct Obj0;
struct Obj1;

struct Obj0 {
    void *m00;
};

struct Obj1 {
    u8 pad000[0x18];
    s32 m18;
};

struct Obj0 *InvViewCtorFromOwner_3cec70(struct Obj0 *p0, struct Obj1 *p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 rv0;
    s32 t0;
    s32 r1;

    p0->m00 = D_00472250;
    p0->m00 = D_004758B0;
    p0->m00 = D_00475890;
    rv0 = 0;
    if (p1 != 0) {
        t0 = p1->m18;
        rv0 = t0;
    }
    r1 = (InvViewInit_3cec40(p0, rv0, p2, p3, p4, p5), (s32)0);
    return p0;
}
