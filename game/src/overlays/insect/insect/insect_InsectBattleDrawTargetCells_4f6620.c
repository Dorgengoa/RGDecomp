/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawTargetCells_4f6620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F6620 -- 388 bytes.  Sibling of insect_FUN_004F67B0: paint every
 * reachable cell in style 3, skipping the cursor cell, then repaint the cursor
 * cell on its own layer at half weight. */

typedef struct Ins {
    u8 pad0000[0x4960];
    u8 f4960[0x8C];                 /* +0x4960 */
    u8 pad49EC[0x4F90 - 0x49EC];
    u8 f4F90[0x40];                 /* +0x4F90 */
} Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

void insect_InsectBattleDrawTargetCells_4f6620(Ins *o, s32 k)
{
    s32  cx;
    s32  cy;
    u8  *g;
    s32  c;
    s32  y;
    s32  x;
    s32  d;

    g = (u8 *)o + 0x4960;
    c = ((s32)DrawListBeginPrim_141b00(k));
    insect_InsectCursorSetGetCell_511a40((u8 *)o + 0x4F90, 0xB, &cx, &cy);
    insect_InsectBattleCellPrimSetup_4f7400(o, c, -1);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (insect_InsectBoardIsTargetMarked_4ee8c0(g, x, y) != 0) {
                if (x != cx || y != cy) {
                    insect_InsectBattleDrawCellQuad_4f6d30(o, c, 3, (f32)x, (f32)y, 0.0f, 1.0f);
                }
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(o, k);
    if (insect_InsectBoardIsTargetMarked_4ee8c0(g, cx, cy) != 0) {
        d = ((s32)DrawListBeginPrim_141b00(k));
        insect_InsectBattleCellPrimSetup_4f7400(o, d, 2);
        insect_InsectBattleDrawCellQuad_4f6d30(o, d, 3, (f32)cx, (f32)cy, 0.0f, 0.5f);
        insect_InsectBattleCellPrimEnd_4f6d20(o, k);
    }
}
