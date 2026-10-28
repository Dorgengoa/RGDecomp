/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuPlacePieceList_4ff350 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FF350 -- 460 bytes, 115 instructions, 13 calls, 6 conditional
 * branches, br/ins 0.052.  A five-phase 0x753B/0x753F/0xC37E driver on the
 * insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 0xB, 0x1D, 0x1C, 0xA, 1 -- REVERSED -- so source order is
 * 1, 0xA, 0x1C, 0x1D, 0xB, matching the block order (0x4FF3C4, 0x4FF41C,
 * 0x4FF454, 0x4FF464, 0x4FF4E8).
 *
 * ★ Case 0xB's `insect_InsectBattleSetState_50d8c0(o, 0xB, ...)` has NO instruction of its own
 * for the 0xB: `$5` still holds the `addiu $5, $0, 0xB` that the case-0xB
 * COMPARE emitted.  An argument with no instruction is the dispatch constant
 * CSE'd into its own arm, not a missing one -- write the literal.
 *
 * The 0x994-strided record is computed BEFORE the switch even though only case
 * 0x1C uses it (its `mult` is hoisted into the prologue for latency), so it is
 * a local assigned up front.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x5EF1 - 0x880];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMenuPlacePieceList_4ff350(Ins *o)
{
    void *r;

    r = (u8 *)o + o->f5EF1 * 0x994 + 0x35F8;
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiFadeWidgetAlpha_290690(o->f878, 0x753F, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    case 0xA:
        if (UiGetWidgetAlpha_290770(o->f878, 0x753F) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        }
        break;
    case 0x1C:
        insect_InsectBattleMemberListGrey_4fae30(o, r);
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x753F, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x753B, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        break;
    case 0xB:
        insect_InsectBattleSetState_50d8c0(o, 0xB, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        break;
    }
}
