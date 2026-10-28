/* rgp:protos */
#define RGP_SELF_DataTableGetIndexSlot_3f5f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x90];
    s32 m90;
};

s32 DataTableGetIndexSlot_3f5f00(struct Obj0 *p0, s32 p1)
{
    return (p0->m90 + (p1 << 2));
}
