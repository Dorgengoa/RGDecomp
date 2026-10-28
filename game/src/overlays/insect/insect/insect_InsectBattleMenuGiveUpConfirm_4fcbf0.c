/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuGiveUpConfirm_4fcbf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FCBF0 -- 876 bytes, 219 instructions, 35 calls, 8 conditional
 * branches, br/ins 0.037.  insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  Compare chain 0xB, 0xA, 0x4B, 0x4A, 0x49,
 * 0x47, 1, so source order is 1, 0x47, 0x49, 0x4A, 0x4B, 0xA, 0xB, with 1
 * falling through into 0x47 and 0x47 into 0x49.
 *
 * 0xA and 0xB are BOTH empty cases and they are an adjacent PAIR: the later one
 * (0xB, tested first) keeps its `beql` to .L004FCF40 while 0xA gets a PLAIN
 * `beq` + `nop` to .L004FCF3C -- the two exit addresses differ by exactly the
 * `ld $31` the branch-likely already ran.  Drop either case and the chain is
 * two words short.
 *
 * Case 1's 0x47 argument is the constant case 0x47's COMPARE built.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x18];          /* +0x5054 */
    u8    f506C[0x4];           /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
} Ins;

extern u8 insect_D_00523FF0[];

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

void insect_InsectBattleMenuGiveUpConfirm_4fcbf0(Ins *o)
{
    s32 x6C;
    s32 x68;
    void *g;
    void *p19;
    void *w;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u8  e;

    g = o->f5054;
    p19 = o->f506C;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectBattleSetStep_50d7a0(o, 0x47, 2, -1);
        /* fallthrough */
    case 0x47:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, p19, 0x12);
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523FF0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x49, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x49, 0, -1);
        /* fallthrough */
    case 0x49:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x6C, &x68);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523FF0, 0);
        w = UiFindWidget_290460(o->f87C, 0xC37B);
        e = !(x6C != 0);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, w, e);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(o->f87C, 0xC37C), x6C);
        break;
    case 0x4A:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        a = insect_InsectBattleGetSavedState_50d5f0(o, 0);
        b = insect_InsectBattleGetSavedStep_50d5e0(o, 0);
        c = insect_InsectBattleGetSavedState_50d5f0(o, 2);
        d = insect_InsectBattleGetSavedStep_50d5e0(o, 2);
        if (insect_InsectBattleTestFlag_50da40(o, 0x37) != 0) {
            insect_InsectBattleClearFlag_50da90(o, 0x37);
            a = insect_InsectBattlePopSavedState_50d590(o, 0);
            b = insect_InsectBattlePopSavedStep_50d540(o, 0);
            c = insect_InsectBattlePopSavedState_50d590(o, 2);
            d = insect_InsectBattlePopSavedStep_50d540(o, 2);
        }
        insect_InsectBattleSetState_50d8c0(o, a, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, b, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, c, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, d, 2, -1);
        insect_InsectCursorSetPopPage_511ca0(o->f4F90);
        o->f4FBC = o->f4FBC & 0xFD;
        break;
    case 0x4B:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetFlag_50dad0(o, 0x40);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    case 0xA:
        break;
    case 0xB:
        break;
    }
}
