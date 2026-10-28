/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawMoveRangeCells_4f67b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F67B0 -- 232 bytes, 58 instructions, 5 calls, 3 conditional
 * branches, br/ins 0.052.  From x_band.py's branch-light band.
 *
 * `(u8 *)o + 0x4960` is computed in the FIRST call's delay slot and parked in
 * $19 for both of its loop sites -- the HOIST polarity of
 * insect-extern-handle-hoist -- so it is a named local, not an array member.
 *
 * Both latches (`slti $2, $16, 0x5` and `slti $2, $17, 0x7`) land in a GPR and
 * not $at, so both are bare `<` (at-compare-class).
 *
 * `mtc1` + `cvt.s.w` is the signed int-to-float path, which a plain `s32`
 * takes; `mtc1 $0, $f14` and `lui 0x3F80` + `mtc1` are the constants 0.0f and
 * 1.0f, both with a zero low half.
 */

typedef struct Ins {
    u8 pad0000[0x4960];
    u8 f4960[0x8C];                 /* +0x4960 */
} Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

void insect_InsectBattleDrawMoveRangeCells_4f67b0(Ins *o, s32 k)
{
    u8  *g;
    s32  c;
    s32  y;
    s32  x;

    g = (u8 *)o + 0x4960;
    c = ((s32)DrawListBeginPrim_141b00(k));
    insect_InsectBattleCellPrimSetup_4f7400(o, c, -1);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (insect_InsectBoardIsMovable_4ee930(g, (long long)(x), (long long)(y)) != 0) {
                insect_InsectBattleDrawCellQuad_4f6d30(o, c, 2, (f32)x, (f32)y, 0.0f, 1.0f);
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(o, k);
}
