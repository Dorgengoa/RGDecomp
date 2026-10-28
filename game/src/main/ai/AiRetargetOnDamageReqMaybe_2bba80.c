/* rgp:protos */
#define RGP_SELF_AiRetargetOnDamageReqMaybe_2bba80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xAC];
    s16 mAC;
    s16 mAE;
    u8 pad0B0[0x8C];
    s16 m13C;
    s16 m13E;
    s16 m140;
    u8 m142;
};

void AiRetargetOnDamageReqMaybe_2bba80(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s16 t0;
    s16 t1;

    t0 = p0->m13C;
    if (t0 == p1) {
        BattleAiRequestTargetRefresh_2cedc0();
    }
    p0->m13C = p1;
    p0->m13E = p4;
    p0->m140 = p5;
    p0->m142 = p3;
    AiAssignTargetIdMaybe_2bbb20(p0, p1);
    t1 = p0->mAE;
    if (t1 != 0x190) {
        if (t1 != 0x12C) {
            p0->mAC = 0x12C;
        }
    }
}
