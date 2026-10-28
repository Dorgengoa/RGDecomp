/* rgp:protos */
#define RGP_SELF_FieldViewResTeardown_202f40 1
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

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FieldViewResTeardown_202f40(void)
{
    s32 r0;
    s32 rv9;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;

    r0 = FieldViewModeGet_2f35a0();
    rv9 = r0;
    if (r0 == 0) {
        r1 = FieldViewModeLeave_2f3660(0xFFFF, 1);
        r2 = GetCurrentScene_1f5be0();
        r3 = ((s32)GetCharaResMgr_1fdb60());
        r4 = ((s32)GetInsectCageMgr_1fdb30());
        r5 = (InsectCageMgrReleaseAll_39a2e0(r4), (s32)0);
        r6 = (InsectCageMgrSetEnabled_39b180(r4, 0), (s32)0);
        r7 = CharaResReleaseAllNpc_1f1070(r3, r2);
        r8 = CharaResReleaseHeapData_1f0f70(r3);
        rv9 = r8;
    }
    return rv9;
}
