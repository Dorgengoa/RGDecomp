/* rgp:protos */
#define RGP_SELF_NavGraphSetXform_310dc0 1
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

struct Obj0 {
    u8 pad000[0x113];
    s8 m113;
};

void NavGraphSetXform_310dc0(struct Obj0 *p0, s32 p1, void *rgp_a2)
{
    s8 t0;

    t0 = p0->m113;
    if (t0 != 0) {
        MatFromRotPos_1caf90(p0, p1, (void *)rgp_a2);
        MtxInverseAffine_1cb640((struct Obj0 *)((u8 *)p0 + 0x40), p0);
    }
}
