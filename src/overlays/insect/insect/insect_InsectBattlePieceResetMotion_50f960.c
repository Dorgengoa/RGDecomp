#include "types.h"
/* insect 0x0050F960 -- 196 bytes.  The global context is fetched FIRST, before
 * the null guard, and survives in $4 to the 0x0050DF60 call. */

typedef struct Obj {
    u8 pad00[0x38];
    s8 f38;                         /* +0x38 */
    u8 pad39[0x4C - 0x39];
    s8 f4C;                         /* +0x4C */
} Obj;

extern void *func_31A8D0(void);
extern void *insect_InsectBattleGetPieceModel_50df60(void *g, Obj *o);
extern void  insect_InsectBattlePieceSetDesignVisible_50fa80(void *r, Obj *o, s32 k);
extern s32   insect_InsectPieceTestStatus_513280(Obj *o, s32 k);
extern void  insect_InsectPiecePlayMotion_5145e0(Obj *o, s32 mode, s32 extra, f32 a, f32 b);

void insect_InsectBattlePieceResetMotion_50f960(Obj *o)
{
    void *g;
    s32   t;
    s32   k;

    g = func_31A8D0();
    if (o == 0) {
        return;
    }
    t = 0;
    k = -1;
    if (o->f38 == 0xC) {
        if (o->f4C > 0) {
            k = 0;
        }
        insect_InsectBattlePieceSetDesignVisible_50fa80(insect_InsectBattleGetPieceModel_50df60(g, o), o, k);
    }
    if (insect_InsectPieceTestStatus_513280(o, 4) != 0) {
        return;
    }
    if (insect_InsectPieceTestStatus_513280(o, 1) != 0) {
        t = 4;
    }
    insect_InsectPiecePlayMotion_5145e0(o, t, 0, 0.0f, 1.0f);
}
