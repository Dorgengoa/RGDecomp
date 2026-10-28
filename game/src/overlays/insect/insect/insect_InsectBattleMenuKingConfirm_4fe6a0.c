/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuKingConfirm_4fe6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FE6A0 -- 1,676 bytes, 419 instructions, 53 calls, 22 conditional
 * branches, br/ins 0.053.  A ten-arm state dispatch on
 * insect_InsectBattleGetStep_50d6a0(o, 2), the same family as insect_InsectBattleMenuTeamSelect_5004f0; read that
 * unit's prototype block first, it is the family's header.
 *
 * The compare chain runs 4, 4A, 4B, 49, 47, 3, 1E, 1D, 1C, 1 -- REVERSED --
 * and the block ADDRESSES run 1, 1C, 1D, 1E, 3, 47, 49, 4B, 4A, 4, which is
 * that same order forwards.  So source case order is the block order, and the
 * 4B/4A pair is out of numeric order because block order is source order and
 * not ascending.
 *
 * Constants CSE'd out of the dispatch into the arm that needs them as
 * ARGUMENTS, exactly as the family note describes -- an argument with no
 * instruction of its own is not a missing instruction:
 *   - case 1's `addiu $6, $0, 0x1` is the case-1 COMPARE's constant, reused as
 *     func_290010's third argument;
 *   - case 4B's `addiu $5, $0, 0x4` is the case-4 compare's constant;
 *   - case 1C's and case 49's `lui $5, %hi(insect_D_00523F30 / insect_D_00523C10)` are in
 *     the dispatch's branch-likely delay slots;
 *   - case 1D's `lui $2, 0x3E000000` (the 0.125f) is in its own beql's slot.
 *
 * The DEFAULT arm branches to one instruction PAST the epilogue head and puts
 * the `ld $31` in its own delay slot, which is why there are two exit labels.
 *
 * insect_InsectCursorSetGetEvents_5119f0's result is held in an s64 -- the `dsll32 $4,$2,0 /
 * dsra32 $4,$4,0` before the `andi 0x80` is the 32->64 sign extension, and an
 * s32 local would test the bit with a bare `andi $3,$2,0x80`.
 */

typedef struct Panel {
    s16 m0, m2, m4, m6, m8, mA, mC, mE;
    f32 m10;                    /* +0x10 */
    f32 m14;                    /* +0x14 */
    s16 m18, m1A;
} Panel;

typedef struct Widget {
    u8    pad00[0x20];
    Panel *m20;                 /* +0x20 */
} Widget;

typedef struct Ins {
    u8   pad0000[0x878];
    void *m878;                 /* +0x0878 */
    void *m87C;                 /* +0x087C */
    u8   pad0880[0x35F8 - 0x880];
    u8   m35F8[0x4F90 - 0x35F8];/* +0x35F8 -- strided by m5EF1 * 0x994 */
    u8   m4F90[0x2C];           /* +0x4F90 */
    u8   m4FBC;                 /* +0x4FBC */
    u8   pad4FBD[0x5054 - 0x4FBD];
    u8   m5054[0x18];           /* +0x5054 */
    u8   m506C[0x5DA0 - 0x506C];/* +0x506C */
    s32  m5DA0;                 /* +0x5DA0 */
    s32  m5DA4;                 /* +0x5DA4 */
    s32  m5DA8;                 /* +0x5DA8 */
    u8   pad5DAC[0x5EF1 - 0x5DAC];
    u8   m5EF1;                 /* +0x5EF1 */
} Ins;

extern u8 insect_D_00523C10[];
extern u8 insect_D_00523F30[];

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
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMenuKingConfirm_4fe6a0(Ins *o)
{
    void *g;
    void *rec;
    Widget *w;
    Panel *q;
    s32 v;
    s32 k;
    s32 i;
    s64 m;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;

    insect_InsectCursorSetGetCell_511a40(o->m4F90, 8, &sp4C, &sp48);
    g = o->m5054;
    rec = o->m35F8 + o->m5EF1 * 0x994;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiSetWidgetVisible_290010(o->m878, 0x7542, 1, -1);
        UiFadeWidgetAlpha_290690(o->m878, 0x7542, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m878, 0x7530, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectCursorSetPushPage_511cf0(o->m4F90, 8, 0);
        o->m4FBC = o->m4FBC & 0xFD;
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523F30, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0x15);
        break;
    case 0x1C:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523F30, 0);
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->m878, 0x7530, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        if (UiGetWidgetAlpha_290770(o->m878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0x1E:
        if (insect_InsectBattleTestFlag_50da40(o, 0x38) != 0) {
            q = ((Widget *)UiFindWidget_290460(o->m878, 0x7546))->m20;
            q->m0 = 0;
            q->m2 = sp48 * 0x1C;
            q->m4 = 0x18;
            q->mC = 0x18;
            q->m6 = 0x18;
            q->mE = 0x18;
            q->m8 = 0xD8;
            q->mA = 0x62;
            q->m1A = 0;
            q->m18 = 0;
            q->m10 = q->m14 = q->m18;
            UiSetWidgetsVisibleById_291110(o->m878, 0x7546, 1, 1);
            UiSetWidgetAlpha_2907a0(o->m878, 0x7546, 0.0f);
            UiFadeWidgetAlpha_290690(o->m878, 0x7546, 1.0f, 0.125f, -1.0f);
            if (o->m5DA8 == 5) {
                UiSetWidgetsVisibleById_291110(o->m878, 0x7546, 0, 1);
            }
            insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        } else {
            insect_InsectBattleSetStep_50d7a0(o, 4, 2, -1);
        }
        break;
    case 3:
        if (UiGetWidgetAlpha_290770(o->m878, 0x7546) < 1.0f) {
            break;
        }
        k = 0x47;
        if (o->m5DA8 == 5) {
            k = 4;
        }
        insect_InsectBattleSetStep_50d7a0(o, k, 2, -1);
        break;
    case 0x47:
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->m5DA0, o->m5DA4, o->m506C, 0x2F);
        insect_InsectCursorSetPushPage_511cf0(o->m4F90, 7, 1);
        o->m4FBC = o->m4FBC & 0xFD;
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 1);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC378, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0x49, 2, -1);
        break;
    case 0x49:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523C10, 0);
        insect_InsectCursorSetGetCurCell_511a90(o->m4F90, &sp44, &sp40);
        w = ((Widget *)UiFindWidget_290460(o->m87C, 0xC37B));
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, w, (u8)!sp44);
        w = ((Widget *)UiFindWidget_290460(o->m87C, 0xC37C));
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, w, sp44);
        m = insect_InsectCursorSetGetEvents_5119f0(o->m4F90, -1);
        v = -1;
        if ((m & 0x80) != 0) {
            v = sp44;
        }
        if ((m & 0x20) != 0 && v == -1) {
            v = 1;
        }
        if (v == -1) {
            break;
        }
        i = 5;
        k = 0x4B;
        if (v != 0) {
            i = 6;
            k = 0x4A;
        }
        insect_InsectBattleSetStep_50d7a0(o, k, 2, -1);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC378, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattlePlaySe_4f45b0(o, i);
        break;
    case 0x4B:
        insect_InsectBattleSetStep_50d7a0(o, 4, 2, -1);
        break;
    case 0x4A:
        rec = insect_InsectTeamGetPiece_5138d0(rec, 0);
        for (i = 0; i < 5; i += 1) {
            insect_InsectPieceClearStatus_513340(rec, 0x1A);
            rec = (u8 *)rec + 0x1E8;
        }
        UiFadeWidgetAlpha_290690(o->m878, 0x7546, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, 0xE, 0, -1);
        break;
    case 4:
        insect_InsectBattleClearFlag_50da90(o, 0x15);
        UiFadeWidgetAlpha_290690(o->m878, 0x7530, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        k = 0xF;
        if (o->m5DA8 == 4) {
            k = 0x24;
        }
        insect_InsectBattleClearFlag_50da90(o, 0x29);
        insect_InsectBattleSetState_50d8c0(o, k, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    }
}
