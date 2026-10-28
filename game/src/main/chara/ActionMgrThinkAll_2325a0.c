/* rgp:protos */
#define RGP_SELF_ActionMgrThinkAll_2325a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x38];
    s32 m38;
};

void ActionMgrThinkAll_2325a0(struct Obj0 *p0)
{
    s32 t0;
    s32 r1;
    s32 l2;
    s32 r4;

    t0 = p0->m38;
    if ((t0 & 0x8000000) == 0) {
        if ((t0 & 0x10000000) == 0) {
            BattleAiTargetUpdate_2ce790();
            r1 = DListGetHead_42ea60((struct Obj0 *)((u8 *)p0 + 0x20));
            l2 = r1;
            while (l2 != 0) {
                CharaAiHandlePrmtRequestsMaybe_20e140((l2 + 0x10));
                r4 = DListGetNext_42eb30(l2);
                l2 = r4;
            }
        }
        return;
    }
}
