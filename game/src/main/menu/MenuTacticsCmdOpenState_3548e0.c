/* rgp:protos */
#define RGP_SELF_MenuTacticsCmdOpenState_3548e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[4]; s16 f4, f6; u8 pad2[0x10 - 8]; s16 f10, f12, f14, f16, f18, f1A; } R_003548e0;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern f32 D_0047D610;
extern s32 D_00482F08;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuTacticsCmdOpenState_3548e0(void)
{
    R_003548e0 *r;

    UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 1.0f, D_0047D610, -1.0f);
    D_00482F08 = 0;
    r = ((R_003548e0 *)UiEntryListFindByTag_28ea40(D_00482364, 0x21));
    r->f16 = 0;
    r->f1A = 0;
    UiSetWidgetPos_290f60(D_00482360, 0x1A6, r->f4, r->f6);
    UiEntryListSelectByTag_28ea90(D_00482364, 0x21, 0);
    StateMachineSetState_28ede0(D_0048235C, 0x9A, 0);
    return 1;
}
