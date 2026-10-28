/* rgp:protos */
#define RGP_SELF_WarpMenuReset_39e020 1
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
    u8 pad000[0x18];
    s32 m18;
    s32 m1C;
    u8 pad020[0x4];
    s16 m24;
    s16 m26;
    s32 m28;
    s32 m2C;
    u8 m30;
    u8 pad031[0x1];
    s16 m32;
    s16 m34;
};

void WarpMenuReset_39e020(struct Obj0 *p0)
{
    s32 l0;

    l0 = 0;
    do {
        LoadHandleReset_1ccc10((u8 *)p0 + (l0 * 12));
        l0 = (l0 + 1);
    } while (l0 < 2);
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m24 = 0;
    p0->m26 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m30 = 0;
    p0->m32 = -1;
    p0->m34 = -1;
}
