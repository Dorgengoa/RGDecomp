/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuOpponentInfo_4ffa80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FFA80 -- 1,532 bytes, 383 instructions, 63 calls, 13 conditional
 * branches, br/ins 0.034.  Same seven-arm state-dispatch family as
 * insect_FUN_005004F0: the compare chain runs 0xE, 0xC, 0x1E, 0x1D, 0x1A,
 * 0x19, 1 and the block ADDRESSES run 1, 0x19, 0x1A, 0x1D, 0x1E, 0xC, 0xE, so
 * source case order is the reverse of the chain, with case 1 falling through
 * into case 0x19.
 *
 * `sltu $3,$0,$3 / xori $3,$3,1 / andi $3,$3,0xFF` on the 0x5EF1 byte is the
 * bool-built-from-an-INEQUALITY-and-negated-in-one-expression idiom held in a
 * `u8`; `o->f5EF1 == 0` gives the shorter `xor / sltiu 1` and is one word
 * fewer.  The `mult` by 0x994 that consumes it is a real source-level multiply
 * -- mwcc could not strength-reduce a non-power-of-two stride.
 */

typedef struct Slot { u8 pad00[0x5C]; s32 f5C; s32 f60; } Slot;

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5DA0 - 0x4FBD];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern u8 insect_D_00523E70[];

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

extern s32  strlen(s32 s);
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

void insect_InsectBattleMenuOpponentInfo_4ffa80(Ins *o)
{
    void *g;
    void *p17;
    void *rec;
    Slot *s;
    s32 i;
    u8 b;

    g = (u8 *)o + 0x5054;
    p17 = (u8 *)o + 0x506C;
    b = !(o->f5EF1 != 0);
    rec = (u8 *)o + b * 0x994 + 0x35F8;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC37E, 0.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC387, 0.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC387, 1.0f, 0.125f, -1.0f);
        InsectBattleMenuFrameNineSliceMaybe_393ac0(g, ((s32)UiFindWidget_290460(o->f87C, 0xC37F)), o->f5DA0 + 0x40, 0x24, 2);
        InsectBattleMenuFrameNineSliceMaybe_393ac0(g, ((s32)UiFindWidget_290460(o->f87C, 0xC381)), 0x160, 0xB2, 0);
        InsectUiTeamIconRowLayoutMaybe_393820(g, ((s32)UiFindWidget_290460(o->f87C, 0xC386)), 0x1C, 1,
                    insect_InsectTeamFindKing_513840(rec));
        InsectBattleMenuFrameNineSliceMaybe_393ac0(g, ((s32)UiFindWidget_290460(o->f87C, 0xC38C)), 0xBC, 0x40, 0);
        UiSetWidgetPos_290f60(o->f87C, 0xC37F, -0x20, 8);
        UiSetWidgetPos_290f60(o->f87C, 0xC380, ((o->f5DA0 - 0x160) / 2) + 0x40,
                    ((o->f5DA4 - 0xB2) / 2) - 0x20);
        UiSetWidgetPos_290f60(o->f87C, 0xC388, 4, 4);
        UiSetWidgetPos_290f60(o->f87C, 0xC38B, 0xA4, 0xBA);
        UiSetTextString_28f510(o->f87C, 0xC37F, ((s32)insect_InsectMsgGet_512b70(p17, 4)), 0);
        UiSetTextPos_28f5d0(o->f87C, 0xC37F,
                    insect_InsectMsgCenterX_512b10(p17, 4, o->f5DA0 + 0x40), 8, 0);
        if (insect_InsectTeamGetName_5138b0(rec) != 0) {
            strlen(insect_InsectTeamGetName_5138b0(rec));
        }
        UiSetTextString_28f510(o->f87C, 0xC382, insect_InsectTeamGetName_5138b0(rec), 1);
        i = 0;
        do {
            s = ((Slot *)insect_InsectTeamGetPiece_5138d0(rec, i));
            if (s != 0) {
                UiSetTextString_28f510(o->f87C, 0xC388, s->f5C, i);
                UiSetTextString_28f510(o->f87C, 0xC38A, s->f60, i);
            }
            i++;
        } while (i < 5);
        UiSetTextString_28f510(o->f87C, 0xC38E, ((s32)insect_InsectMsgGet_512b70(p17, 5)), 0);
        UiSetTextString_28f510(o->f87C, 0xC38E, ((s32)insect_InsectMsgGet_512b70(p17, 6)), 1);
        UiSetWidgetVisible_290010(o->f87C, 0xC37F, 1, -1);
        UiSetWidgetVisible_290010(o->f87C, 0xC387, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x19, 2, -1);
        /* fallthrough */
    case 0x19:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523E70, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1A, 2, -1);
        break;
    case 0x1A:
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523E70, 0);
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC387, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 0), 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetSavedStep_50d5e0(o, 0), 0, -1);
        insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 2), 2, -1);
        insect_InsectCursorSetPopPage_511ca0(o->f4F90);
        break;
    case 0x1E:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC387, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        break;
    case 0xC:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC387, 0.0f, 0.125f, -1.0f);
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC387) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xD, 2, -1);
        }
        insect_InsectBattleClearFlag_50da90(o, 0x1D);
        break;
    case 0xE:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC387, 1.0f, 0.125f, -1.0f);
        insect_InsectBattlePopStep_50d760(o, 2);
        insect_InsectBattlePopStep_50d760(o, 2);
        insect_InsectBattlePopStep_50d760(o, 2);
        insect_InsectBattleSetFlag_50dad0(o, 0x1D);
        break;
    }
}
