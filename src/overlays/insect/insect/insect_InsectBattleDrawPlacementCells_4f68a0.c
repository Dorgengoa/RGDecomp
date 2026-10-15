#include "types.h"
/* insect 0x004F68A0 -- 436 bytes.  Two painters over the same layer: with the
 * flag set, five entries out of the 0x4920 table; otherwise a 2x5 block of
 * grid cells offset by the team base, with the cursor cell picked out. */

typedef struct Ins {
    u8 pad0000[0x4920];
    u8 f4920[0x20];                 /* +0x4920 */
    u8 pad4940[0x4960 - 0x4940];
    u8 f4960[0x8C];                 /* +0x4960 */
    u8 pad49EC[0x4F90 - 0x49EC];
    u8 f4F90[0x40];                 /* +0x4F90 */
    u8 pad4FD0[0x5EF1 - 0x4FD0];
    u8 f5EF1;                       /* +0x5EF1 */
} Ins;

extern void insect_InsectCursorSetGetCell_511a40(u8 *t, s32 k, s32 *px, s32 *py);
extern s32  func_141B00(s32 k);
extern void insect_InsectBattleCellPrimSetup_4f7400(Ins *o, s32 c, s32 k);
extern void insect_InsectTeamSlotGetCell_513d90(u8 *t, s32 i, s32 *px, s32 *py, s32 f);
extern void insect_InsectBattleDrawCellQuad_4f6d30(Ins *o, s32 c, s32 m, f32 x, f32 y,
                                f32 a, f32 b);
extern s32  insect_InsectBoardGetPiece_4ee9a0(u8 *g, s16 x, s16 y);
extern void insect_InsectBattleCellPrimEnd_4f6d20(Ins *o, s32 k, s32 c);

void insect_InsectBattleDrawPlacementCells_4f68a0(Ins *o, s32 k, s32 mode)
{
    s32  cx;
    s32  cy;
    s32  ex;
    s32  ey;
    s32  base;
    u8  *t;
    u8  *g;
    s32  c;
    s32  x;
    s32  y;

    base = 0;
    if (o->f5EF1 == 0) {
        base += 5;
    }
    t = (u8 *)o + (o->f5EF1 << 5) + 0x4920;
    g = (u8 *)o + 0x4960;
    insect_InsectCursorSetGetCell_511a40((u8 *)o + 0x4F90, 9, &cx, &cy);
    c = func_141B00(k);
    insect_InsectBattleCellPrimSetup_4f7400(o, c, -1);
    if (mode != 0) {
        for (x = 0; x < 5; x++) {
            insect_InsectTeamSlotGetCell_513d90(t, x, &ex, &ey, o->f5EF1);
            insect_InsectBattleDrawCellQuad_4f6d30(o, c, 2, (f32)ex, (f32)ey, 0.0f, 1.0f);
        }
    } else {
        for (y = 0; y < 2; y++) {
            for (x = 0; x < 5; x++) {
                if (insect_InsectBoardGetPiece_4ee9a0(g, (s16)x, (s16)(y + base)) == 0) {
                    s32 m;

                    m = 2;
                    if (x == cx && y == cy) {
                        m = 1;
                    }
                    insect_InsectBattleDrawCellQuad_4f6d30(o, c, m, (f32)x, (f32)(y + base), 0.0f, 1.0f);
                }
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(o, k, c);
}
