/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuVictoryCondSelect_4fb7c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FB7C0 -- 640 bytes, 160 instructions, 25 calls, 6 conditional
 * branches, br/ins 0.037.  A five-phase 0x765C/0x765D/0x765E widget driver on
 * the insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 5, 4, 3, 2, 1 -- REVERSED -- so source order is 1, 2, 3, 4, 5,
 * which is also the block order (0x4FB81C, 0x4FB8E4, 0x4FB97C, 0x4FB994,
 * 0x4FB9EC).  There are no empty cases: the DEFAULT is the one that gets the
 * epilogue-head-PLUS-ONE target (`b .L004FBA34` with `ld $31` in its own delay
 * slot) while every case arm branches to the head itself.
 *
 * o->f506C is REMATERIALISED at all four of its sites (bare
 * `addiu $4, $16, 0x506C`), so it is an array member.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x506C - 0x880];
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
} Ins;

extern u8 insect_D_005240B0[];

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

void insect_InsectBattleMenuVictoryCondSelect_4fb7c0(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiSetWidgetVisible_290010(o->f878, 0x765C, 1, -1);
        UiSetTextString_28f510(o->f878, 0x765D, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x3E8)), 0);
        UiSetTextPos_28f5d0(o->f878, 0x765D,
                    insect_InsectMsgCenterX_512b10(o->f506C, 0x3E8, o->f5DA0 + 0x40),
                    0xA, 0);
        UiSetTextString_28f510(o->f878, 0x765E, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x3EA)), 0);
        UiSetTextString_28f510(o->f878, 0x765E, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x3E9)), 1);
        UiSetWidgetVisible_290010(o->f87C, 0xC37E, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        break;
    case 2:
        UiSetWidgetAlpha_2907a0(o->f878, 0x765C, 0.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x765C, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_005240B0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
        break;
    case 3:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_005240B0, 0);
        break;
    case 4:
        UiFadeWidgetAlpha_290690(o->f878, 0x765C, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 5, 2, -1);
        break;
    case 5:
        if (UiGetWidgetAlpha_290770(o->f878, 0x765C) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 6, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
        }
        break;
    }
}
