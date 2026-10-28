/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuOpponentIntroClose_5010e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005010E0 -- 212 bytes, 53 instructions.
 * A three-arm dispatch on insect_InsectBattleGetStep_50d6a0(o, 2).  The compare chain is
 * 0xB / 0xA / 1 while the arms are laid out 1 / 0xA / 0xB, i.e. the
 * [[insect-dispatch-branch-polarity]] `beql` INTO the arm = a switch whose
 * case order is the REVERSE of the compare chain.
 * 0x3E000000 = 0.125f and 0xBF800000 = -1.0f are lui-only bit patterns, so
 * they are materialised in a GPR and moved with mtc1 rather than pooled.
 */

typedef struct Obj {
    u8  pad000[0x878];
    s32 m878;                       /* +0x878 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMenuOpponentIntroClose_5010e0(Obj *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiFadeWidgetAlpha_290690(o->m878, 0x7534, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    case 0xA:
        if (UiGetWidgetAlpha_290770(o->m878, 0x7534) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0xB:
        insect_InsectBattleSetState_50d8c0(o, 0, 2, -1);
        break;
    }
}
