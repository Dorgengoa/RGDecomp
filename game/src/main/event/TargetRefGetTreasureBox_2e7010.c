/* rgp:protos */
#define RGP_SELF_TargetRefGetTreasureBox_2e7010 1
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
    u8 pad000[0x4];
    s32 m04;
};

s32 TargetRefGetTreasureBox_2e7010(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;

    r0 = ((short)TargetRefGetKind_2e7130(p0));
    if (r0 == 0xB) {
        t0 = p0->m04;
        return t0;
    }
    return 0;
}
