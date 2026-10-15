#include "types.h"
/* insect 0x00517C80 -- 268 bytes, 67 instructions.
 *
 * A guard cascade followed by a three-arm dispatch on `o->fC` whose compares
 * are `beql` INTO the blocks, so it is a `switch` written 0, 1, default
 * (the compare chain 1, 0 REVERSED).
 */

typedef struct Ctx {
    u8  pad0000[0x5EF8];
    s32 f5EF8;                      /* +0x5EF8 */
} Ctx;

typedef struct Obj {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
    u8  pad08[0x4];
    s32 fC;                         /* +0x0C */
} Obj;

extern Ctx *func_31A8D0(void);
extern void insect_InsectBattleCamSave_4f1b50(Ctx *c);
extern s32  insect_InsectBattleGetActorSlot_50db40(Ctx *c, s32 k);
extern s32  insect_InsectPieceHasLandedHitMaybe_512e10(s32 a);
extern s32  insect_InsectPieceTestStatus_513280(s32 a, s32 k);

s32 insect_InsectSeqExecCamReset_517c80(Obj *o)
{
    Ctx *c;
    s32 a;
    s32 b;

    c = func_31A8D0();
    if (o == 0 || c == 0) {
        return 1;
    }
    a = insect_InsectBattleGetActorSlot_50db40(c, 0);
    b = insect_InsectBattleGetActorSlot_50db40(c, 1);
    if (a == 0) {
        return 1;
    }
    if (insect_InsectPieceHasLandedHitMaybe_512e10(a) == 0) {
        return 1;
    }
    if (b != 0) {
        if (insect_InsectPieceTestStatus_513280(b, 5) == 0) {
            return 1;
        }
    }
    if (o->f4 != 0) {
        return 0;
    }
    switch (o->fC) {
    case 0:
        c->f5EF8 = 0xB;
        break;
    case 1:
        insect_InsectBattleCamSave_4f1b50(c);
        c->f5EF8 = 4;
        break;
    default:
        c->f5EF8 = 0xB;
        break;
    }
    return 1;
}
