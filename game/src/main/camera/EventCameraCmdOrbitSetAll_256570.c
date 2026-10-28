/* rgp:protos */
#define RGP_SELF_EventCameraCmdOrbitSetAll_256570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x50];
    f32 m50;
    f32 m54;
    f32 m58;
    u8 pad05C[0x4];
    f32 m60;
    f32 m64;
    f32 m68;
    u8 pad06C[0x4];
    f32 m70;
    f32 m74;
    f32 m78;
    s32 m7C;
    u8 pad080[0x20];
    f32 mA0;
    f32 mA4;
    f32 mA8;
};

struct Obj1 {
    u8 pad000[0x10];
    f32 m10;
    f32 m14;
    f32 m18;
};

s32 EventCameraCmdOrbitSetAll_256570(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 t0;
    s32 rv2;
    f32 rv3;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 r0;
    f32 t5;
    f32 t6;
    f32 t7;
    f32 t8;
    f32 t9;
    f32 r1;
    f32 t10;
    f32 t11;
    f32 t12;
    f32 t13;
    f32 t14;

    t0 = p1->m7C;
    rv2 = 0;
    if (t0 != 0) {
        t1 = p0->m10;
        p1->mA0 = t1;
        t2 = p0->m14;
        p1->mA4 = t2;
        t3 = p0->m18;
        p1->mA8 = t3;
        rv2 = t0;
        rv3 = t3;
    } else {
        t4 = p0->m10;
        r0 = Sinf_128fd0(t4);
        t5 = p1->m60;
        t6 = p0->m18;
        p1->m50 = (t5 + (t6 * r0));
        t7 = p0->m14;
        t8 = p1->m64;
        p1->m54 = (t7 + t8);
        t9 = p0->m10;
        r1 = Cosf_128d30(t9);
        t10 = p1->m68;
        t11 = p0->m18;
        p1->m58 = (t10 + (t11 * r1));
        t12 = p0->m10;
        p1->m70 = t12;
        t13 = p0->m14;
        p1->m74 = t13;
        t14 = p0->m18;
        p1->m78 = t14;
        rv2 = 0;
        rv3 = t14;
    }
    return 0;
}
