/* rgp:protos */
#define RGP_SELF_FontGetGaijiHeight_26f860 1
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
    u8 pad000[0x8];
    s8 m08;
};

s32 FontGetGaijiHeight_26f860(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s8 t0;

    r0 = FontFindGaijiMetric_26f8c0(p0, (p1 & 0xFFFF));
    if (r0 != 0) {
        t0 = r0->m08;
        return t0;
    }
    return 0;
}
