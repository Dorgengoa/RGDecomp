/* rgp:protos */
#define RGP_SELF_ShopParamSetShopIdMaybe_3e8460 1
#include "port/game_protos.h"
#line 1
#include "types.h"



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
    struct Obj1 *m08;
};

struct Obj1 {
    u8 pad000[0xA8];
    struct Obj2 *mA8;
};

struct Obj2 {
    u8 pad000[0xC];
    struct Obj3 *m0C;
};

struct Obj3 {
    u8 pad000[0x9C];
    s16 m9C;
};

s32 ShopParamSetShopIdMaybe_3e8460(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    s32 rv0;
    struct Obj2 * t1;
    struct Obj3 * t2;

    t0 = p0->m08;
    rv0 = 1;
    if (t0 == 0) {
        rv0 = 0;
    } else {
        t1 = p0->m08->mA8;
        t2 = p0->m08->mA8->m0C;
        p0->m08->mA8->m0C->m9C = p1;
        rv0 = 1;
    }
    return rv0;
}
