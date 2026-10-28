/* rgp:protos */
#define RGP_SELF_EvObjReset_2f9eb0 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0xD0];
    s32 mD0;
    s32 mD4;
    s32 mD8;
};

void EvObjReset_2f9eb0(struct Obj0 *p0)
{
    EventRecReset_2e5840(p0);
    p0->mD0 = 0;
    p0->mD4 = 0;
    p0->mD8 = 0;
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xA0));
    XformInitIdentity_2e7970((struct Obj0 *)((u8 *)p0 + 0x58));
    XformInitIdentity_2e7970((struct Obj0 *)((u8 *)p0 + 0x10));
}
