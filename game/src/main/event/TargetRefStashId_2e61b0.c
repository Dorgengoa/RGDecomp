/* rgp:protos */
#define RGP_SELF_TargetRefStashId_2e61b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
    u8 pad004[0x8];
    s32 m0C;
};

s32 TargetRefStashId_2e61b0(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;
    s16 t1;

    r0 = ((short)TargetRefGetKind_2e7130(p0));
    if (r0 != 9) {
        if (r0 != 7) {
            return r0;
        }
        t0 = p0->m02;
        p0->m0C = t0;
        p0->m02 = -1;
        return r0;
    }
    t1 = p0->m02;
    p0->m0C = t1;
    p0->m02 = -1;
    return r0;
}
