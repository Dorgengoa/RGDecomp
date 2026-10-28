/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellTabsSwitchCb_5103f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P3F0S {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} P3F0S;

typedef struct P3F0G {
    u8 pad00[0x10];
    s8 f10;
    s8 f11;
} P3F0G;

typedef struct P3F0C {
    u8    pad00[0x18];
    void *f18;
} P3F0C;

extern f32    D_0047D240;         /* gp - 0x7F30 */
extern P3F0G *D_004845D4;         /* gp - 0xB9C  */
extern void  *D_004845A8;         /* gp - 0xBC8  */
extern s32    D_00484680;         /* gp - 0xAF0  */
extern u8     D_004B2570[];

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
/*rgp*/

s32 normal_ShopMenuSellTabsSwitchCb_5103f0(P3F0S *a)
{
    P3F0C *ctx;
    s32    max;
    u8    *pad;
    s32    cur;
    s32    ok;

    pad = D_004B2570;
    cur = D_004845D4->f11;
    max = D_004845D4->f10;
    ok = 0;
    if (PadIsTriggered_1839f0(pad, 4) != 0) {
        if (cur > 0) {
            cur--;
            ok = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 4) == 0) {
            cur = max - 1;
            ok = 1;
        }
    } else if (PadIsTriggered_1839f0(pad, 8) != 0) {
        if (cur < max - 1) {
            cur++;
            ok = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 8) == 0) {
            cur = 0;
            ok = 1;
        }
    }
    if (ok != 0) {
        D_004845D4->f11 = cur;
        normal_ShopMenuSellTabsLayout_50e980(0x38, cur);
        MenuItemGridMarkInUse_2a4860(D_004845D4, 0x3C);
        MenuFillItemGrid_2a4b40(D_004845D4, 0x3D);
        MenuFillItemCounts_2a3d90(D_004845D4, 0x3E);
        ctx = ((P3F0C *)GetGameData_1fede0());
        normal_ShopMenuItemInfoShow_509520(((P3F0C *)InvFindByCategoryIndex_3c86e0(ctx->f18, 0, cur, a->f10, a->f12, 0)),
                            0x34, 0x33, 0x57, 0x15E, D_0047D240);
        SoundPlayScaledVolume_1b9520(D_004845A8, 0xB, 0, 1.0f);
        D_00484680 = 0;
        normal_ShopMenuSellCellHintShow_50f650(0);
    }
    return 1;
}
