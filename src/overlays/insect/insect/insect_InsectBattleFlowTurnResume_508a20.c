#include "types.h"
/* insect 0x00508A20 -- 268 bytes, 67 instructions. */

typedef struct Obj {
    u8  pad00[0x5EF1];
    u8  f5EF1;                      /* +0x5EF1 */
} Obj;

extern s32 insect_InsectBattleIsSideAi_4f1950(Obj *a, s32 k);
extern void insect_InsectBattleCursorNextPiece_4f0bd0(Obj *a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern s32 insect_InsectBattleGetStep_50d6a0(Obj *a, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Obj *a, s32 b, s32 c, s32 d);
extern void insect_InsectBattleSetState_50d8c0(Obj *a, s32 b, s32 c, s32 d);
extern s32 insect_InsectBattleTestFlag_50da40(Obj *a, s32 k);
extern void insect_InsectBattleSetFlag_50dad0(Obj *a, s32 k);

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
