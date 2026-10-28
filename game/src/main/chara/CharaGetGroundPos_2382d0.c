/* rgp:protos */
#define RGP_SELF_CharaGetGroundPos_2382d0 1
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
    u8 pad000[0x70];
    f32 m70;
    u8 pad074[0x4];
    f32 m78;
    u8 pad07C[0x35C];
    s32 m3D8;
    u8 pad3DC[0x10];
    f32 m3EC;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    s32 m0C;
};

s32 CharaGetGroundPos_2382d0(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 rv0;
    f32 t1;
    f32 t2;
    f32 t3;

    t0 = p0->m3D8;
    rv0 = 1;
    if ((t0 & 4) == 0) {
        rv0 = 0;
    } else {
        t1 = p0->m70;
        p1->m00 = t1;
        t2 = p0->m3EC;
        p1->m04 = t2;
        t3 = p0->m78;
        p1->m08 = t3;
        p1->m0C = 0x3F800000;
        rv0 = 1;
    }
    return rv0;
}
