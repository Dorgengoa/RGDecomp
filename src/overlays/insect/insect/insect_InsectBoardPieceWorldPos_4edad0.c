#include "types.h"
/* insect 0x004EDAD0 -- 176 bytes, 44 instructions.
 *
 * $4/$5 are passed straight through to insect_InsectBoardFindPiece_4ee190; the two out-params
 * live at $29+0x4C and $29+0x48, i.e. stack locals in REVERSE declaration
 * order.  _gp - 0x78F8 is D_0047D878.
 */

extern const f32 D_0047D878 __attribute__((section(".sdata")));
extern s32 insect_InsectBoardFindPiece_4ee190(void *a, void *b, s32 *x, s32 *y);

void insect_InsectBoardPieceWorldPos_4edad0(void *a, void *b, f32 *px, f32 *py, f32 *pz)
{
    s32 c;
    s32 r;
    f32 g;

    switch (insect_InsectBoardFindPiece_4ee190(a, b, &c, &r)) {
    case 1:
        g = D_0047D878;
        *px = 4.0f * (f32)(c - 2);
        *py = g;
        *pz = 4.0f * (f32)(r - 3);
        break;
    case 0:
        *px = 0.0f;
        *py = 0.0f;
        *pz = 0.0f;
        break;
    }
}
