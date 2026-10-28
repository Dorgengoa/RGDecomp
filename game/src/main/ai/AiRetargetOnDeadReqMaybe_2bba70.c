/* rgp:protos */
#define RGP_SELF_AiRetargetOnDeadReqMaybe_2bba70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xAC];
    s16 mAC;
    u8 pad0AE[0x8E];
    s16 m13C;
};

void AiRetargetOnDeadReqMaybe_2bba70(struct Obj0 *p0, s32 p1)
{
    p0->m13C = p1;
    p0->mAC = 0x190;
    BattleAiRequestTargetRefresh_2cedc0();
}
