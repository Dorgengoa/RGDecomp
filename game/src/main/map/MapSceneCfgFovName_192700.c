/* rgp:protos */
#define RGP_SELF_MapSceneCfgFovName_192700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004812F4;
extern s32 D_004812F8;

struct Obj0;

struct Obj0 {
    u8 pad000[0x1D4];
    s32 m1D4;
};

s32 MapSceneCfgFovName_192700(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 t0;
    s32 r1;
    struct Obj0 * t1;

    r0 = SlotGetInt_15f720(p0);
    rv2 = 1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        t0 = D_004812F8;
        r1 = ((s32)MemStackStrDup_14cff0(r0, t0));
        t1 = D_004812F4;
        D_004812F4->m1D4 = r1;
        rv2 = 1;
    }
    return rv2;
}
