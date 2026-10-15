#include "types.h"
/* insect 0x0051B000 -- 192 bytes, 48 instructions, 6 calls. */

extern void *func_31A8D0(void);
extern void *insect_InsectBattleGetActorSlot_50db40(void *h, s32 k);
extern void *insect_InsectBattleAttackResolve_4f3480(void *h);
extern s32   insect_InsectPieceTestStatus_513280(void *p, s32 k);
extern void  insect_InsectBattleApplyDamage_50f350(void *a, void *b, void *c, s32 d, s32 e);

s32 insect_InsectSeqExecImpact_51b000(void *p)
{
    void *h;
    void *a;
    void *b;
    void *c;

    h = func_31A8D0();
    if (p == 0 || h == 0) {
        return 1;
    }
    a = insect_InsectBattleGetActorSlot_50db40(h, 0);
    b = insect_InsectBattleGetActorSlot_50db40(h, 1);
    if (b == 0 || a == 0) {
        return 1;
    }
    c = insect_InsectBattleAttackResolve_4f3480(h);
    if (insect_InsectPieceTestStatus_513280(a, 0xF) == 0) {
        insect_InsectBattleApplyDamage_50f350(a, b, c, 0, 0);
    }
    return 1;
}
