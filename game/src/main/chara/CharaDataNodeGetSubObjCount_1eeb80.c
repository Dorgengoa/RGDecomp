/* rgp:protos */
#define RGP_SELF_CharaDataNodeGetSubObjCount_1eeb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2A];
    s16 m2A;
    s32 m2C;
};

s16 CharaDataNodeGetSubObjCount_1eeb80(struct Obj0 *p0)
{
    s32 t0;
    s16 t1;

    t0 = p0->m2C;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m2A;
    return t1;
}
