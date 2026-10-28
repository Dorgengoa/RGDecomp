/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowTurnResume_508a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00508A20 -- 268 bytes, 67 instructions. */

typedef struct Obj {
    u8  pad00[0x5EF1];
    u8  f5EF1;                      /* +0x5EF1 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowTurnResume_508a20(Obj *a)
{
    s32 k;
    s32 m;

    switch (insect_InsectBattleGetStep_50d6a0(a, 0)) {
    case 1:
        if (insect_InsectBattleIsSideAi_4f1950(a, a->f5EF1) == 0) {
            insect_InsectBattleSetFlag_50dad0(a, 0x15);
            insect_InsectBattleSetFlag_50dad0(a, 0x27);
        }
        insect_InsectBattleSetStep_50d7a0(a, 0xA, 0, -1);
        insect_InsectBattleCursorNextPiece_4f0bd0(a, 2, 0, 1, -1, 0);
        insect_InsectBattleSetState_50d8c0(a, 1, 5, -1);
        break;
    case 0xA:
        k = 0x10;
        m = 0;
        if (a->f5EF1 == 1) {
            m = 1;
        }
        if (insect_InsectBattleTestFlag_50da40(a, m) != 0) {
            k = 0x11;
        }
        insect_InsectBattleSetState_50d8c0(a, k, 0, -1);
        break;
    case 0xB:
        break;
    }
}
