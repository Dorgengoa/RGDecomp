/* rgp:protos */
#define RGP_SELF_NpcObjSaveMarkPos_2fb920 1
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
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj2 *m08;
};

struct Obj1 {
    u8 pad000[0xA0];
    f32 mA0;
    f32 mA4;
    f32 mA8;
    u8 pad0AC[0x8];
    f32 mB4;
    u8 pad0B8[0xE];
    s16 mC6;
};

struct Obj2 {
    u8 pad000[0x6C];
    s32 m6C;
};

struct Obj3 {
    u8 pad000[0x38];
    f32 m38;
    f32 m3C;
    f32 m40;
    f32 m44;
};

struct Obj3 *NpcObjSaveMarkPos_2fb920(struct Obj1 *p0)
{
    struct Obj0 *r0;
    struct Obj2 * t0;
    s16 t1;
    s32 t2;
    struct Obj3 *r1;
    f32 t3;
    f32 t4;
    f32 t5;
    f32 t6;

    r0 = GetGameData_1fede0();
    t0 = r0->m08;
    t1 = p0->mC6;
    t2 = r0->m08->m6C;
    r1 = GroupGetRecordById_41c2a0(t2, (long long)(t1), (long long)(-1), 1);
    if (r1 != 0) {
        t3 = p0->mA0;
        r1->m38 = t3;
        t4 = p0->mA4;
        r1->m3C = t4;
        t5 = p0->mA8;
        r1->m40 = t5;
        t6 = p0->mB4;
        r1->m44 = t6;
    }
    return r1;
}
