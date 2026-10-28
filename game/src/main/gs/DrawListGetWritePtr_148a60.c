/* rgp:protos */
#define RGP_SELF_DrawListGetWritePtr_148a60 1
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
    u8 pad000[0x28];
    s32 m28;
    s32 m2C;
};

s32 DrawListGetWritePtr_148a60(s32 p0)
{
    struct Obj0 *r0;
    s32 rv1;
    s32 t0;
    s32 t1;

    r0 = DrawListGetCurBuf_142790(p0);
    rv1 = (t1 + (t0 << 4));
    if (r0 == 0) {
        rv1 = 0;
    } else {
        t0 = r0->m2C;
        t1 = r0->m28;
        rv1 = (t1 + (t0 << 4));
    }
    return rv1;
}
