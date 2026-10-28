/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawWebCells_4f4bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F4BF0 -- 272 bytes, 68 instructions.  A 7x5 u8 flag grid at
 * +0x4A9B (the `sll 2` + `addu` is i*5) tested against 0x10.  Both loop
 * indices are converted to float into CALLEE-SAVED $f20/$f21 BEFORE the inner
 * call, so each conversion is its own named local -- the j one first -- and the
 * inner call's result is a third named local. */

typedef struct Obj {
    u8 pad0000[0x4960];
    u8 f4960[0x4A9B - 0x4960];      /* +0x4960 */
    u8 f4A9B[7][5];                 /* +0x4A9B */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleDrawWebCells_4f4bf0(Obj *o, void *a)
{
    void *r;
    s32 i;
    s32 j;

    r = DrawListBeginPrim_141b00(a);
    insect_InsectBattleCellPrimSetup_4f7400(o, r, 8);
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 5; j++) {
            if ((o->f4A9B[i][j] & 0x10) != 0) {
                insect_InsectBattleDrawCellQuad_4f6d30(o, r, 7, (f32)j, (f32)i, 0.0f,
                                    insect_InsectBoardWebFadeGet_4ee5a0(o->f4960, j, i));
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(o, a);
}
