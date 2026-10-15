#include "types.h"
/* insect 0x004F4D00 -- 268 bytes.  A 7x5 sweep of the grid at +0x4960; the
 * cell value is fetched TWICE (once for the test, once as the last float
 * argument) because insect_InsectBoardHoleFadeGet_4ee650 is a call and cannot be CSE'd. */

typedef struct Obj {
    u8 pad0000[0x4960];
    u8 f4960[0x4F90 - 0x4960];      /* +0x4960 */
} Obj;

extern void *func_141B00(void *p);
extern f32   insect_InsectBoardHoleFadeGet_4ee650(void *g, s32 x, s32 y);
extern void  insect_InsectBattleCellPrimEnd_4f6d20(Obj *o, void *a, void *h);
extern void  insect_InsectBattleDrawCellQuad_4f6d30(Obj *o, void *h, s32 k, f32 x, f32 y, f32 z, f32 v);
extern void  insect_InsectBattleCellPrimSetup_4f7400(Obj *o, void *h, s32 k);

void insect_InsectBattleDrawHoleCells_4f4d00(Obj *o, void *a)
{
    void *h;
    s32 y;
    s32 x;

    h = func_141B00(a);
    insect_InsectBattleCellPrimSetup_4f7400(o, h, -1);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (insect_InsectBoardHoleFadeGet_4ee650(o->f4960, x, y)) {
                insect_InsectBattleDrawCellQuad_4f6d30(o, h, 6, (f32)x, (f32)y, 0.0f,
                                    insect_InsectBoardHoleFadeGet_4ee650(o->f4960, x, y));
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(o, a, h);
}
