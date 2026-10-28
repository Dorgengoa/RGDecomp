/* rgp:protos */
#define RGP_SELF_EvTargetMapObjDisable_352560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x34];
    s32 m34;
};

struct Obj1 {
    u8 pad000[0x32];
    s16 m32;
    u8 pad034[0x8];
    s32 m3C;
};

void EvTargetMapObjDisable_352560(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *r0;
    struct Obj1 * rv1;
    s32 t1;

    t0 = p0->m34;
    if (t0 != 0) {
        r0 = TargetRefGetMapObj_2e7050(p0);
        rv1 = 0;
        if (r0 != 0) {
            r0->m32 = 0;
            t1 = r0->m3C;
            r0->m3C = (t1 | 1);
            rv1 = r0;
        }
        return;
    }
}
