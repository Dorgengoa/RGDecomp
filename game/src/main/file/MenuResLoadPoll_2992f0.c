/* rgp:protos */
#define RGP_SELF_MenuResLoadPoll_2992f0 1
#include "port/game_protos.h"
#line 1
/* PARKED: 3 round trips: shared-epilogue restructure + if-polarity flip (both levers) got it to exact length (67w) with only 4/67 bad words -- very close, worth a follow-up read of the remaining diff. */
#include "types.h"
#pragma opt_lifetimes off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482338;
extern s32 D_004823FC;
extern s32 D_00482410;
extern u8 D_004DB260[0x70];

s32 MenuResLoadPoll_2992f0(void)
{
    s32 sp3C;
    s32 temp_2;
    s32 var_16;
    void *temp_17;

    var_16 = 0;
    do {
        temp_17 = D_004DB260 + (var_16 * 0x38);
        if ((LoadHandleGetId_28b220(temp_17) != -1) && (((unsigned char)LoadHandleIsPending_28b210(temp_17)) != 0) && (LoadHandleGetStatus_28b2e0(temp_17) == 1)) {
            GetDrawCtxNameTable_15de40();
            temp_2 = LoadHandleGetData_28b270(temp_17, &sp3C);
            if (var_16 == 1) {
                LoadHandleRegisterData_28b320(temp_17, D_004823FC, 0x32E, D_00482338);
                MainMenuBuildIconMaskClut_2994d0();
            } else if (var_16 == 0) {
                MenuModelCreate_294330(temp_2);
            }
            LoadHandleFree_28b230(temp_17);
        }
        var_16 += 1;
    } while (var_16 < 2);
    if (((unsigned char)LoadHandlesAllReady_28b070(D_004DB260, 2)) == 1) {
        D_00482410 = 1;
        temp_2 = 1;
    } else {
        temp_2 = 0;
    }
    return temp_2;
}
