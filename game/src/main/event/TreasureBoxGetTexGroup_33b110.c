/* rgp:protos */
#define RGP_SELF_TreasureBoxGetTexGroup_33b110 1
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

struct Obj0 {
    u8 pad000[0x68];
    struct Obj1 *m68;
};

struct Obj1 {
    u8 pad000[0x4];
    struct Obj2 *m04;
};

struct Obj2 {
    u8 pad000[0x30];
    s32 m30;
};

s32 TreasureBoxGetTexGroup_33b110(struct Obj0 *p0)
{
    struct Obj1 * t0;
    struct Obj2 * t1;
    s32 t2;

    t0 = p0->m68;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m68->m04;
    if (t1 != 0) {
        t2 = p0->m68->m04->m30;
        return t2;
    }
    return 0;
}
