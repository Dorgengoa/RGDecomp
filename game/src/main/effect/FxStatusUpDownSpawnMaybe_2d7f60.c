/* rgp:protos */
#define RGP_SELF_FxStatusUpDownSpawnMaybe_2d7f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004616B0[];

void FxStatusUpDownSpawnMaybe_2d7f60(s32 p0)
{
    u128 v30[2];
    s32 r0;

    r0 = ((s32)GetEffectMgr_2d9040());
    EffectCreateByName_2e1020(v30, r0, D_004616B0, -1);
    EffectSetId_2e0100(r0, v30, p0);
    EffectSetParamInt_2e0530(r0, v30, 0, 1);
}
