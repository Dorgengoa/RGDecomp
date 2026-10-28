/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyListCursorBobCb_50dd20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050DD20 -- per-frame tick of the spinning 0x2F widget plus two
 * independent frame counters (0x3C and 0x50 phase edges). */

typedef struct Obj { u8 pad00[0x16]; s16 f16; } Obj;

extern f32   D_00484648;          /* gp - 0xB28  */
extern void *D_004845C8;          /* gp - 0xBA8  */
extern s32   D_0048464C;          /* gp - 0xB24  */
extern s16   D_0048463C;          /* gp - 0xB34  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyListCursorBobCb_50dd20(Obj *o)
{
    s32 x;
    s32 y;
    f32 v;
    s32 n;

    PhaseAdvanceWrapPi_28b630(&D_00484648, 0.0785398185f);
    v = 8.0f * Sinf_128fd0(D_00484648);
    GetGridCellPosOffset_28ecd0(o, &x, &y, (s32)v, 0);
    UiMoveWidgetUniform_290f50(D_004845C8, 0x2F, x, y, 0.25f, 0);

    if (D_0048464C < 0x3C) {
        n = D_0048464C + 1;
        D_0048464C = n;
        if (n == 0x3C) {
            normal_ShopMenuBuyRowHintShow_50c550(1);
        }
    }
    if (D_0048463C < 0x50) {
        n = D_0048463C + 1;
        D_0048463C = n;
        if ((s16)n == 0x28) {
            normal_ShopMenuBuyRowIconsRefresh_50dae0(o->f16, 1);
        } else if ((s16)n == 0x50) {
            normal_ShopMenuBuyRowIconsRefresh_50dae0(o->f16, 0);
            D_0048463C = 0;
        }
    }
    return 1;
}
