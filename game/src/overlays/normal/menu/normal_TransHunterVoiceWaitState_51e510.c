/* rgp:protos */
#define RGP_SELF_normal_TransHunterVoiceWaitState_51e510 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051E510 -- twin of normal_FUN_0051EA30.  Sibling of the settled
 * seed normal_FUN_0051E5F0 (same widget family, same 0x7919 id, same
 * `extern f32 D_0047D9C0` gp float spelling).
 *
 * The `daddu $16,$2,$0` in func_207290's DELAY SLOT captures func_2072C0's
 * return, so the two calls are two locals evaluated BEFORE the || chain --
 * that is why func_207290 is not short-circuited.  func_207290 returns a f32
 * in $f0 (its $2 is unused).
 */

extern void *D_0048470C;          /* gp - 0xA64 */
extern void *D_00484710;          /* gp - 0xA60 */
extern void *D_00484718;          /* gp - 0xA58 */
extern f32   D_0047D9C0;          /* gp - 0x77B0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterVoiceWaitState_51e510(void *a, s32 b)
{
    s32 st;
    f32 t;

    if (b != 0) {
        StreamChan1SetVolumeFade_2072f0(0xF, 0.0f);
        UiFadeWidgetAlpha_290690(D_00484718, 0x7919, 0.0f, D_0047D9C0, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7633, 0, 1);
    }
    st = StreamChan1GetStatus_2072c0();
    t = StreamChan1GetVolume_207290();
    if (st == -2 || st == 0 || st == 2 || t <= 0.0f) {
        StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 1.0f);
        StateMachineSetState_28ede0(D_0048470C, 0x19, 0);
    }
    return 1;
}
