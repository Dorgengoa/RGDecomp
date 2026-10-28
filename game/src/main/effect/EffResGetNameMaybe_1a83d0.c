/* rgp:protos */
#define RGP_SELF_EffResGetNameMaybe_1a83d0 1
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
    u8 pad000[0x8];
    struct Obj1 *m08;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 EffResGetNameMaybe_1a83d0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 t1;

    t0 = p0->m08;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m08->m0C;
    if (t1 != 0) {
        return (t1 + 8);
    }
    return 0;
}
