/* rgp:protos */
#define RGP_SELF_EvCmdAbilityReqResReloadMaybe_25eaa0 1
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

extern u8 D_0048218C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

s32 EvCmdAbilityReqResReloadMaybe_25eaa0(void)
{
    s32 r0;
    struct Obj0 *r1;
    s32 t0;
    s32 t1;
    s32 r2;

    r0 = (EventObjMgrSuspend_27aef0(), (s32)0);
    r1 = GetAbilityReq_27a640();
    if (r1 != 0) {
        t0 = r1->m08;
        t1 = r1->m04;
        r2 = CharaAbilityResReloadMaybe_2f3f10(t1, t0);
    }
    D_0048218C = 1;
    return 1;
}
