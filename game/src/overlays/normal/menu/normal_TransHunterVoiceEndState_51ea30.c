/* rgp:protos */
#define RGP_SELF_normal_TransHunterVoiceEndState_51ea30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051EA30 -- twin of normal_FUN_0051E510, shorter tail. */

extern void *D_0048470C;          /* gp - 0xA64 */
extern void *D_00484718;          /* gp - 0xA58 */
extern u16   D_004848C0;          /* gp - 0x8B0 */
extern f32   D_0047D9C0;          /* gp - 0x77B0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterVoiceEndState_51ea30(void *a, s32 b)
{
    s32 st;
    f32 t;

    if (b != 0) {
        StreamChan1SetVolumeFade_2072f0(0xF, 0.0f);
        UiFadeWidgetAlpha_290690(D_00484718, 0x7919, 0.0f, D_0047D9C0, -1.0f);
    }
    st = StreamChan1GetStatus_2072c0();
    t = StreamChan1GetVolume_207290();
    if (st == -2 || st == 0 || st == 2 || t <= 0.0f) {
        StateMachineSetState_28ede0(D_0048470C, D_004848C0, 0);
    }
    return 1;
}
