/* rgp:protos */
#define RGP_SELF_CharaSysSetStealthTimer_3a1ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004837C0;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;
struct Obj4;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj1 *m08;
};

struct Obj1 {
    u8 pad000[0x54];
    struct Obj2 *m54;
};

struct Obj2 {
    u8 pad000[0x8];
    struct Obj3 *m08;
};

struct Obj3 {
    u8 pad000[0xC4];
    s16 mC4;
};

struct Obj4 {
    u8 pad000[0x250];
    f32 m250;
};

s32 CharaSysSetStealthTimer_3a1ca0(struct Obj4 *p0, f32 fa0)
{
    struct Obj0 * t0;
    struct Obj0 * rv0;
    f32 rv1;
    struct Obj1 * t1;
    struct Obj2 * t2;
    struct Obj3 * t3;
    s16 t4;

    t0 = D_004837C0;
    if (t0 == 0) {
        return 0;
    }
    rv0 = (struct Obj0 *)t0;
    rv1 = 0.0f;
    if (fa0 <= 0.0f) {
        t1 = D_004837C0->m08;
        t2 = D_004837C0->m08->m54;
        t3 = D_004837C0->m08->m54->m08;
        t4 = D_004837C0->m08->m54->m08->mC4;
        p0->m250 = ((f32)t4);
        rv0 = (struct Obj0 *)t4;
        rv1 = ((f32)t4);
    } else {
        p0->m250 = fa0;
        rv0 = (struct Obj0 *)t0;
        rv1 = 0.0f;
    }
    return 1;
}
