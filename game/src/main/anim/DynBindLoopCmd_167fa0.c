/* rgp:protos */
#define RGP_SELF_DynBindLoopCmd_167fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00481154;

struct Obj0;

struct Obj0 {
    u8 pad000[0xF4];
    s32 mF4;
};

s32 DynBindLoopCmd_167fa0(s32 p0)
{
    s32 r;

    r = VariantGetInt_15f780(p0);
    D_00481154->mF4 = r;
    return 1;
}
