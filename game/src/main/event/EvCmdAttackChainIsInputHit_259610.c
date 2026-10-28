/* rgp:protos */
#define RGP_SELF_EvCmdAttackChainIsInputHit_259610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    u8 m00[8];
    u8 m08[8];
};

s32 EvCmdAttackChainIsInputHit_259610(struct Obj0 *p0, s32 p1)
{
    void *h;

    if (p1 != 2) {
        return 0;
    }
    h = GetAttackChain_1fdb40();
    ScriptSetRefInt_26a1e0(p0->m08, AttackChainIsInputHit_382c10(h, ScriptGetInt_26a2a0(p0->m00)));
    return 1;
}
