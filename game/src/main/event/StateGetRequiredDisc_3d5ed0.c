/* rgp:protos */
#define RGP_SELF_StateGetRequiredDisc_3d5ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483938;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

u8 StateGetRequiredDisc_3d5ed0(void)
{
    s32 r;

    r = ((short)StateGetChapter_3cd5b0(D_00483938->m10));
    return ((r >= 8) & 0xFF);
}
