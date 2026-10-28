/* rgp:protos */
#define RGP_SELF_ItemKindBelow4_3d4860 1
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
    u8 pad000[0x10];
    s32 m10;
};

s32 ItemKindBelow4_3d4860(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;

    t0 = p0->m10;
    if (t0 != 0) {
        r0 = ItemDefKindBelow4_40e430(t0);
        return r0;
    }
    return 0;
}
