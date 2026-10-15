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

extern s32 insect_InsectBattleGetStep_50d6a0(Obj *, s32);
extern void insect_InsectBattleSetStep_50d7a0(Obj *, s32, s32, s32);
extern void insect_InsectBattleSetState_50d8c0(Obj *, s32, s32, s32);
extern void func_290690(s32, s32, f32, f32, f32);
extern f32 func_290770(s32, s32);

void insect_InsectBattleMenuOpponentIntroClose_5010e0(Obj *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_290690(o->m878, 0x7534, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    case 0xA:
        if (func_290770(o->m878, 0x7534) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0xB:
        insect_InsectBattleSetState_50d8c0(o, 0, 2, -1);
        break;
    }
}
