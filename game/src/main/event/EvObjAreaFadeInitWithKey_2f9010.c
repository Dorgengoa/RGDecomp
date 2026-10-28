/* rgp:protos */
#define RGP_SELF_EvObjAreaFadeInitWithKey_2f9010 1
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
    u8 pad000[0xE2];
    s16 mE2;
};

void EvObjAreaFadeInitWithKey_2f9010(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    EvObjAreaFadeReset_2f90a0(p0);
    EvObjInitWithKey_2f9e60(p0, p1, p2);
    TargetRefSetMapObj_2e6470((struct Obj0 *)((u8 *)p0 + 0xA0), p3, p4, 0.0f);
    p0->mE2 = p5;
}
