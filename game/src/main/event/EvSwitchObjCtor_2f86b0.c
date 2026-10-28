/* rgp:protos */
#define RGP_SELF_EvSwitchObjCtor_2f86b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471820[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvSwitchObjCtor_2f86b0(struct Obj0 *p0)
{
    s32 r0;
    s32 r2;

    r0 = ((s32)EvObjCtor_2f9f00(p0));
    p0->mDC = D_00471820;
    TargetRefCtor_2e71f0((struct Obj0 *)((u8 *)p0 + 0xE0));
    r2 = (EvSwitchObjReset_2f8670(p0), (s32)0);
    return p0;
}
