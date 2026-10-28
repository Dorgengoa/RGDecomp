/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuDetailInfo_500080 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00500080 -- 340 bytes, 85 instructions, 16 calls, 3 conditional
 * branches, br/ins 0.035.  A two-phase 0xC350 driver on the
 * insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 0x1D, 1 -- REVERSED -- so source order is 1, 0x1D, which is the
 * block order (0x5000B8, 0x500134).  The default `b`s to 0x005001C8, the
 * epilogue head PLUS ONE, with `ld $31` in its own delay slot.
 *
 * o->f5B30 is REMATERIALISED at its one site (`addiu $5, $16, 0x5B30` straight
 * into the argument register), so it is an array member, not a local.
 */

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8    pad880[0x5B30 - 0x880];
    u8    f5B30[4];             /* +0x5B30 */
} Ins;

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

void insect_InsectBattleMenuDetailInfo_500080(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiSetWidgetVisible_290010(o->f87C, 0xC350, 1, -1);
        insect_InsectBattleParamWindowLayout_4f3620(o, o->f5B30);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC350, 0.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC350, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC350, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 2), 2, -1);
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x29D);
        insect_InsectBattleClearFlag_50da90(o, 0x1C);
        if (insect_InsectBattleTestFlag_50da40(o, 0x36) != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0xE, 1, -1);
            insect_InsectBattleClearFlag_50da90(o, 0x36);
        }
        break;
    }
}
