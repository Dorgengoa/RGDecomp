/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuTacticsCloseState_4fd060 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FD060 -- the 0x35 frame's fade driver.  Sibling of
 * normal_FUN_004FD2D0 on the same gp handle D_0048449C; here NEITHER argument
 * is read, both guards are float tests and every path returns 1.
 *
 * `lwc1 $f1, 0x0($2)` off func_2904B0's return makes that call an `f32 *`
 * deref; `c.le.s $f1,$f0` against an inline 1.0f is a direct `<= 1.0f`.
 * The second `mtc1 $0,$f1 / c.le.s $f0,$f1 / bc1fl` is `<= 0.0f`.
 * `lh $5, 0x14($2)` is func_28EA40's record read AT ITS USE as argument two.
 */

typedef struct Hdl { u8 pad00[0x14]; s16 f14; } Hdl;

extern u8 normal_D_00527020[];

extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D51C;          /* gp - 0x7C54 */
extern void *D_00484498;          /* gp - 0xCD8  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuTacticsCloseState_4fd060(void *a, s32 b)
{
    if (*((f32 *)UiGetWidgetColor_2904b0(D_0048449C, 0x38)) <= 1.0f) {
        UiMoveWidgetUniform_290f50(D_0048449C, 0x35, -0x1E, 0xF8, D_0047D248, 0);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x35, 0.0f, D_0047D51C, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_0048449C, 0x35) <= 0.0f) {
        normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, ((Hdl *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55F2))->f14);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x35, 0, 1);
        StateMachineSetState_28ede0(D_00484498, 0x55F6, 0);
    }
    return 1;
}
