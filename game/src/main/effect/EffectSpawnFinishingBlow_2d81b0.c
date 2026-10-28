/* rgp:protos */
#define RGP_SELF_EffectSpawnFinishingBlow_2d81b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004616D8[];

s32 EffectSpawnFinishingBlow_2d81b0(s32 p0)
{
    u128 v60;
    u128 v50;
    u128 v30[2];
    s32 r0;
    s32 r1;
    s32 r3;

    r0 = GetCurrentScene_1f5be0();
    r1 = ((s32)ObjRecGetLiveObject_1c4a90(r0, p0));
    if (r1 != 0) {
        if(!ObjGetNthAttachPointPosSafe_23b0c0(r1,0,0,&v60))return;
        v50=*(u128*)(r1+0x190);
        r3 = ((s32)GetEffectMgr_2d9040());
        EffectCreateByName_2e1020(v30, r3, D_004616D8, -1);

        EffectSetId_2e0100(r3, v30, p0);
        EffectSetPos_2e0bb0(r3, v30, &v60);
        EffectSetRot_2e09f0(r3,v30,&v50);
    }
}
