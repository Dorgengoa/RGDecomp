/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuTeamSelBanner_4fb510 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FB510 -- 684 bytes, 171 instructions, 23 calls, 9 conditional
 * branches, br/ins 0.053.  The 0xC38F-0xC392 confirm-panel driver on the
 * insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 4, 3, 2, 1 -- REVERSED -- so source order is 1, 2, 3, 4, and
 * `case 3: break;` is EMPTY: its `beql` targets 0x004FB7AC, the epilogue head
 * PLUS ONE, because the branch-likely already ran `ld $31` in its delay slot.
 * Case 4's block is the last one and falls straight into the epilogue head.
 *
 * o->f5054 and o->f506C are REMATERIALISED (bare `addiu $4, $16, K`) so they
 * are array members; o->f5F82 is HOISTED into $17 for its two uses, so that one
 * is a local -- insect-array-member-blocks-cse, both halves.
 *
 * ★ `daddiu $2, $0, 0x1` for the `v = 1` arm is the tell that `v` is an
 * UNSIGNED NARROW type: the trailing `andi $2, $2, 0xFF` before the `sll 4`
 * confirms `u8`.  An `s32` v drops the mask and is two words short.
 */

typedef struct Node {
    u8  pad00[8];
    s16 f8;                     /* +0x08 */
} Node;

typedef struct Widget {
    u8    pad00[0x20];
    Node *f20;                  /* +0x20 */
} Widget;

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4FBC - 0x880];
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x506C - 0x5054]; /* +0x5054 */
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern void    Sprintf_1343b8(void *p, s32 a, s32 b);
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

void insect_InsectBattleMenuTeamSelBanner_4fb510(Ins *o)
{
    void *p;
    Node *n;
    s32 m;
    u8 v;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiWindowFrameLayoutMaybe_392bb0(o->f5054, ((Widget *)UiFindWidget_290460(o->f87C, 0xC390)), 0x168, 0x40, 0);
        InsectUiWindowFillSetSizeMaybe_3938f0(o->f5054, ((Widget *)UiFindWidget_290460(o->f87C, 0xC391)), 356.0f, 60.0f);
        p = (u8 *)o + 0x5F82;
        Sprintf_1343b8(p, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x3EB)), o->f5EF1 + 1);
        UiSetTextString_28f510(o->f87C, 0xC390, p, 0);
        UiSetTextPos_28f5d0(o->f87C, 0xC390, 0x40, 8, 0);
        UiSetWidgetVisible_290010(o->f87C, 0xC38F, 1, -1);
        UiSetWidgetVisible_290010(o->f87C, 0xC392, 0, -1);
        UiSetWidgetPos_290f60(o->f87C, 0xC390, (o->f5DA0 - 0x168) / 2,
                    (o->f5DA4 - 0x40) / 2);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC38F, 0.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC38F, 1.0f, 0.125f, -1.0f);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC3A3, 1.0f);
        n = ((Widget *)UiFindWidget_290460(o->f87C, 0xC3A5))->f20;
        m = 4 << o->f5EF1;
        if (m == 0xFF) {
            v = o->f4FBC;
        } else if ((o->f4FBC & m) != 0) {
            v = 1;
        } else {
            v = 0;
        }
        n->f8 = v * 0x10 + 0x2C;
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        break;
    case 2:
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC38F) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
        }
        break;
    case 3:
        break;
    case 4:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        break;
    }
}
