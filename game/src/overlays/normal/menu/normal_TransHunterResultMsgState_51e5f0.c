/* rgp:protos */
#define RGP_SELF_normal_TransHunterResultMsgState_51e5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051E5F0 -- 0x7919-widget phase handler, same 0x34-Layout family as
 * normal_FUN_0050F960 (identical frame: -0x50, Layout at sp+0x10, memset 0x34,
 * `sh $2,0x40($29)`).
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  The `b .L0051E70C`
 * at the end of the guarded block makes this an if/ELSE, not a fall-through.
 * func_28F620's result is used BOTH as an s16 pair (`lh 0x0` / `lh 0x2`, fed to
 * func_290F60) and as the Layout's f04, so it is spelled as a pointer.
 * `lui 0x3F80 / mtc1` is 1.0f inline; the middle float is the gp literal
 * D_0047D998 (gp - 0x77D8).  The else arm's `addiu $3,$0,1` + `bne $2,$3` is a
 * plain `== 1` against the signed return.
 */

typedef struct Layout {
    void *f00;
    s16  *f04;
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

extern f32   D_0047D998;          /* gp - 0x77D8 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484718;          /* gp - 0xA58  */
extern void *D_00484720;          /* gp - 0xA50  */

extern void  memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterResultMsgState_51e5f0(void *a, s32 b)
{
    Layout lay __attribute__((aligned(16)));
    s16 *p;

    if (b != 0) {
        p = ((s16 *)UiGetWidgetText_28f620(D_00484718, 0x7919, 0));
        UiSetWidgetPos_290f60(D_00484718, 0x791A, p[0], p[1]);
        UiFadeWidgetAlpha_290690(D_00484718, 0x7919, 1.0f, D_0047D998, 0.0f);

        memset(&lay, 0, 0x34);
        lay.f00 = UiGetWidgetSprite_28fe10(D_00484718, 0x7919, 0);
        lay.f04 = ((s16 *)UiGetWidgetText_28f620(D_00484718, 0x7919, 0));
        lay.f10 = 0x3C;
        lay.f14 = 0x28;
        lay.f18 = 0x1E;
        lay.f1C = 8;
        lay.f20 = 0x49;
        lay.f24 = 0x49;
        lay.f28 = 0x19C;
        lay.f2C = 0x136;
        lay.f30 = 4;
        UiWindowFitToText_28d0c0(&lay, 0, 0, 0);
    } else {
        if (MenuGridCursorInput_28e170(D_00484720, D_004B2570, 0, 0) == 1) {
            StateMachineSetState_28ede0(D_0048470C, 0x18, 0);
        }
    }
    return 1;
}
