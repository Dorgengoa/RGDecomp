/* rgp:protos */
#define RGP_SELF_normal_TransSaveSlotCursorBob_518990 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518990 -- same 6.0f bias as 0x005188C0, but the bias is passed as
 * an INT argument to func_28ECD0 and the tail splits on the third parameter
 * between the 4-arg func_290F60 and the 6-arg func_290F50 (5 ints $4-$8 plus
 * one float in $f12). */

extern f32 D_004847E4;   /* gp - 0x98C  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_TransSaveSlotCursorBob_518990(void *a, void *b, s32 c)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_004847E4, 0.078539818525314331f);
    GetGridCellPosOffset_28ecd0(a, &x, &y, (s32)(6.0f * Sinf_128fd0(D_004847E4)), 0);
    if (c != 0) {
        UiSetWidgetPos_290f60(b, 0x75A2, x, y);
    } else {
        UiMoveWidgetUniform_290f50(b, 0x75A2, x, y, 0.25f, 0);
    }
}
