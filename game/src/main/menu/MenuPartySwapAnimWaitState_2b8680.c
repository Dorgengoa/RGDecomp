/* rgp:protos */
#define RGP_SELF_MenuPartySwapAnimWaitState_2b8680 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's `((var_16*4)+sp)->unk20` is the
 * same ambiguous local-array-on-stack address pattern seen in AttackChainMarkersShow_382c40 --
 * m2c's ADDRESS math for the local array does not resolve cleanly without a
 * manual asm trace. Deferred to preserve lane throughput.
 * See asm/matchings/main/MenuPartySwapAnimWaitState_2b8680.s. */
/* s49m: MATCH */
#include "types.h"

extern s32 D_00482370;
extern s32 D_00482360;
extern s32 D_0048235C;
extern u8 D_004DB730[];
extern u8 D_004DB760[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuPartySwapAnimWaitState_2b8680(s32 arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 i;
    s32 v;
    s32 *p;
    s32 w;

    if (arg1 != 0) {
        s32 buf[2];

        MenuGetSwapPair_29f970(D_00482370, &buf[0], &buf[1]);
        for (i = 0; i < 2; i++) {
            p = &buf[i];
            v = *p;
            if (v < 3) {
                w = (u16)(v + 0xF5);
            } else {
                w = (u16)(v + 0xF8);
            }
            UiSetWidgetsVisibleById_291110(D_00482360, w, 0, 1);
        }
        MenuPartySwapAnimStart_29b5a0(D_00482370, buf[0], buf[1]);
    }
    UiGetWidgetPos_2910a0(D_00482360, 0x11F, &a, &b);
    p = ((s32 *)MenuGetMoveTarget_29f9e0(D_00482370));
    if (a == p[0] && b == p[1]) {
        StateMachineSetState_28ede0(D_0048235C, 0x56, 1);
    }
    UiSelFrameAnimStep_28d820(D_004DB730, 0x14B);
    UiSelFrameAnimStep_28d820(D_004DB760, 0x14C);
    return 1;
}
