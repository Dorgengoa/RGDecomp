/* rgp:protos */
#define RGP_SELF_normal_TransMenuNoticeState_514880 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514880 -- 0x764E-widget phase handler, 0x34-Layout family.
 * Frame is -0x60 because one callee-saved GPR is live across a call in the
 * else arm (`sq $16` at sp+0x00, `sd $31` at sp+0x10), which pushes the Layout
 * to sp+0x20 and the `sh` to 0x50.
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  The guarded block
 * ends in `b .L005149F0`, so this is if/ELSE.  In the guard the func_290690
 * floats are 0.0f then the gp literal D_0047D9F8 (gp - 0x7778) then -1.0f, the
 * SWAPPED order of the seed.  The else arm's `addiu $2,$16,-1 / sltiu $1,$2,2`
 * is an UNSIGNED range test on the func_28E170 result, so its return is spelled
 * u32.  `addiu $4,$28,-0xA70` is the ADDRESS of small-data D_00484700.
 */

typedef struct Layout {
    void *f00;
    s32   f04;
    u8    pad08[8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    s32   f2C;
    s16   f30;
} Layout;

extern u8 D_004B2570[];
extern u8    normal_D_00527EE0[];

extern f32   D_0047D9F8;          /* gp - 0x7778 */
extern s32   D_00484700;          /* gp - 0xA70  */
extern void *D_004846E8;          /* gp - 0xA88  */

extern void  memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuNoticeState_514880(void *a, s32 b)
{
    Layout lay __attribute__((aligned(16)));
    u32 r;

    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_004846E8, 0x7556, 0.0f, D_0047D9F8, -1.0f);

        memset(&lay, 0, 0x34);
        lay.f00 = UiGetWidgetSprite_28fe10(D_004846E8, 0x764E, 0);
        lay.f04 = ((s32)UiGetWidgetText_28f620(D_004846E8, 0x764E, 0));
        lay.f10 = 0x3C;
        lay.f14 = 0xC;
        lay.f18 = 0x1C;
        lay.f1C = 8;
        lay.f20 = 0x62;
        lay.f24 = 0x49;
        lay.f28 = 0x186;
        lay.f2C = 0x12C;
        lay.f30 = 4;
        UiWindowFitToText_28d0c0(&lay, 0, 0, 0);

        UiSetWidgetsVisibleById_291110(D_004846E8, 0x764E, 1, 1);
        UiEntryListSelectByTag_28ea90(normal_D_00527EE0, 0xF, 0);
        MenuGridCursorInput_28e170(normal_D_00527EE0, D_004B2570, 0, 0);
    } else {
        r = MenuGridCursorInput_28e170(normal_D_00527EE0, D_004B2570, 0, 0);
        UiEntryListGetCurrentData_28ec60(normal_D_00527EE0);
        if (r - 1 < 2) {
            UiSetWidgetsVisibleById_291110(D_004846E8, 0x764E, 0, 1);
            StateMachineSetState_28ede0(&D_00484700, 3, 0);
        }
    }
    return 1;
}
