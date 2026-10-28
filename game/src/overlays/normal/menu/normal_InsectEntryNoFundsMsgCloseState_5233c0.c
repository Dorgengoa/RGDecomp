/* rgp:protos */
#define RGP_SELF_normal_InsectEntryNoFundsMsgCloseState_5233c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005233C0 -- the 0x1E-widget phase handler's CLOSE half, the direct
 * sibling of src/wf/normal/normal_InsectEntryNoFundsMsgOpenState_523450.c: same static widget
 * normal_D_005281A0, same id 0x1E, same small-data D_004849A8 tail post.
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  The guarded block
 * is one func_290690 with (0.0f, pool literal, -1.0f).  The tail test is
 * `c.le.s $f0,$f1` against an inline 0.0f with `bc1fl` PAST the block, so the
 * source test is written `<= 0.0f` and the block is the fall-through side --
 * the opposite polarity to the seed's `>= 1.0f`.
 * `addiu $4,$28,-0x7C8` is the ADDRESS of the small-data object D_004849A8.
 */

extern u8    normal_D_005281A0[];

extern f32   D_0047D7D0;          /* gp - 0x79A0 */
extern s32   D_004849A8;          /* gp - 0x7C8  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_InsectEntryNoFundsMsgCloseState_5233c0(void *a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(normal_D_005281A0, 0x1E, 0.0f, D_0047D7D0, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(normal_D_005281A0, 0x1E) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(normal_D_005281A0, 0x1E, 0, 1);
        StateMachineSetState_28ede0(&D_004849A8, 0x7532, 1);
    }
    return 1;
}
