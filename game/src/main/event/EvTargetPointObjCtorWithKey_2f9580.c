/* rgp:protos */
#define RGP_SELF_EvTargetPointObjCtorWithKey_2f9580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EvTargetPointObjCtorWithKey_2f9580 -- constructor-shaped: forwards to EvObjCtor_2f9f00,
   installs the D_00471910 table pointer at +0xDC, forwards to
   EvTargetPointObjInitWithKey_2f9470 and returns `this`. */

/*rgp*/
/*rgp*/
extern u8 D_00471910[];

u8 *EvTargetPointObjCtorWithKey_2f9580(u8 *p, s32 a, s32 b, s32 c, s32 d, s32 e, f32 fa, f32 fb)
{
    EvObjCtor_2f9f00(p);
    *(u8 **)(p + 0xDC) = D_00471910;
    EvTargetPointObjInitWithKey_2f9470(p, a, b, c, d, e, fa, fb);
    return p;
}
