/* rgp:protos */
#define RGP_SELF_SavePointActivate_426480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483F38;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

struct Obj1 {
    s16 m00;
    u8 pad002[0xA];
    s16 m0C;
    u8 pad00E[0x32];
    s32 m40;
};

struct Obj2 {
    u8 pad000[0xC];
    struct Obj3 *m0C;
    u8 pad010[0x8];
    s32 m18;
};

struct Obj3 {
    u8 pad000[0x8];
    s64 m08;
};

s32 SavePointActivate_426480(struct Obj1 *p0, s32 p1, s32 p2, s32 p3, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4, f32 fa5, f32 fa6, f32 fa7)
{
    struct Obj0 * t0;
    s32 t1;
    s16 t2;
    s32 t3;
    struct Obj2 *rv2;
    struct Obj0 * t4;
    s32 t5;
    struct Obj0 * t6;
    struct Obj0 * t7;
    struct Obj3 * t8;
    s64 t9;
    s32 r3;
    double r4;
    s16 t10;
    s32 t11;

    t0 = D_00483F38;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_00483F38->m10;
    t2 = p0->m0C;
    StateFlag256Set_3cc4c0(t1, t2, 1);
    t3 = p0->m40;
    if ((t3 & 2) == 0) {
        t4 = D_00483F38;
        t5 = D_00483F38->m18;
        PartyFullRestoreAll_3c0930(t5);
        t6 = D_00483F38;
        rv2 = (struct Obj2 *)t6;
    } else {
        t7 = D_00483F38;
        rv2 = (struct Obj2 *)t7;
    }
    t8 = rv2->m0C;
    t9 = rv2->m0C->m08;
    r3 = DoubleToU64_13ab28(__builtin_bit_cast(double, (long long)(t9)));
    r4 = U64ToDouble_100370((unsigned long long)(r3));
    t10 = p0->m00;
    t11 = rv2->m18;
    SavePointStoreLast_3c97b0(t11, t10, (long long)__builtin_bit_cast(long long, (double)(r4)));
    return 1;
}
