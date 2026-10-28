/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuLayoutPlace_4ff520 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FF520 -- 1,372 bytes, 343 instructions.
 *
 * A fourteen-label dispatch with four MERGED case groups.  The compare chain
 * is 0x1D, 0x1C, 0xA, 0x4B, 0x4A, 0x50, 0x4F, 0x49, 0x4E, 0x48, 0x4D, 0x47,
 * 0x4C, 1, so the SOURCE order is that chain REVERSED and the arm addresses
 * ascend in exactly that order.  Inside a merged group the FIRST-tested label
 * is the LAST written: it gets the `beql` that copies the arm's first
 * instruction into its delay slot, and the others get a plain `beq` to the
 * un-copied entry one word earlier.
 *
 * Case 0xA never sets $5 -- it inherits the `addiu $5, $0, 0x1C` built for
 * case 0x1C's own compare, which is the compare-chain-constant-is-the-arm's-
 * argument rule; the argument must be written as the same literal 0x1C.
 *
 * The 0x994 record stride is byte arithmetic on the raw object pointer
 * (`addiu $2,$0,0x994` / `mult` / `addu` / `addiu 0x35F8`), not a struct array.
 * `ori $5, $0, 0xC37E` rather than `addiu` is a u16 id above 0x7FFF.
 */

typedef struct Ctx {
    u8   pad0000[0x878];
    s32  f878;                      /* +0x0878 */
    s32  f87C;                      /* +0x087C */
    u8   pad0880[0x4F90 - 0x880];
    u8   f4F90[0x4FBC - 0x4F90];    /* +0x4F90 */
    u8   f4FBC;                     /* +0x4FBC */
    u8   pad4FBD[0x5054 - 0x4FBD];
    u8   f5054[0x506C - 0x5054];    /* +0x5054 */
    u8   f506C[0x5DA0 - 0x506C];    /* +0x506C */
    s32  f5DA0;                     /* +0x5DA0 */
    s32  f5DA4;                     /* +0x5DA4 */
    u8   pad5DA8[0x5EF1 - 0x5DA8];
    u8   f5EF1;                     /* +0x5EF1 */
} Ctx;

extern u8 insect_D_00523C10[];
extern u8 insect_D_00523EA0[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMenuLayoutPlace_4ff520(Ctx *o)
{
    s32   a;
    s32   b;
    void *m;
    void *base;
    s32   v;
    s32   ok;
    s32   i;
    s32   t;

    m = o->f5054;
    base = (u8 *)o + o->f5EF1 * 0x994 + 0x35F8;
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        if (UiWidgetIsMoving_290d30(o->f878, 0x753E) == 0) {
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523EA0, 1);
            UiSetWidgetVisible_290010(o->f878, 0x7542, 1, -1);
            UiSetWidgetAlpha_2907a0(o->f878, 0x7542, 0.0f);
            UiFadeWidgetAlpha_290690(o->f878, 0x7542, 1.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        }
        break;
    case 0x4C:
    case 0x47:
        UiFadeWidgetAlpha_290690(o->f878, 0x7555, 1.0f, 0.125f, -1.0f);
        v = 0x44;
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            v = 0x26;
        }
        UiSetWidgetPos_290f60(o->f878, 0x7556, 0, 0xF6 - v);
        v = 0x29;
        if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0x4C) {
            v = 0x2A;
        }
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, o->f506C, v);
        insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, 2) + 1, 2, -1);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 1);
        break;
    case 0x4D:
    case 0x48:
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, 2), 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, 2) + 1, 2, -1);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 1);
        }
        break;
    case 0x4E:
    case 0x49:
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 7, &a, &b);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 0);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(m, UiFindWidget_290460(o->f87C, 0xC37B), (u8)!a);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(m, UiFindWidget_290460(o->f87C, 0xC37C), a);
        break;
    case 0x4F:
    case 0x50:
    case 0x4A:
    case 0x4B:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, 2), 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x46, 2, -1);
        break;
    case 0xA:
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        break;
    case 0x1C:
        UiFadeWidgetAlpha_290690(o->f878, 0x7530, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523EA0, 0);
        insect_InsectBattleMemberListGrey_4fae30(o, base);
        ok = 1;
        for (i = 0; i < 5; i++) {
            t = ((s32)insect_InsectTeamGetPiece_5138d0(base, i));
            if (t != 0 && insect_InsectPieceTestStatus_513280(t, 0x21) == 0) {
                ok = 0;
                break;
            }
        }
        if (ok != 0) {
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
            o->f4FBC |= 2;
            insect_InsectBattleSetState_50d8c0(o, 0xB, 0, -1);
        }
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->f878, 0x7530, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        if (UiGetWidgetAlpha_290770(o->f878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    }
}
