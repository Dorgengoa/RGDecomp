/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuConfirmCloseState_520120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520120 -- the shop/talk portrait panel's tear-down, the mirror of
 * normal_ThinkMenuConfirmOpenState_520320: on `b != 0` it fades the 0x753C frame out and the
 * 0x7544 frame in.  The tail is the SAME tail 0x00520320 ends with --
 * normal_ThinkMenuPromptScrollStep_521660(func_1CEBA0(func_1F5BE0())) then event 0x7532 posted at
 * &D_00484928 -- and it runs on every call.
 *
 * D_00484928 has its ADDRESS taken (`addiu $4,$28,-0x848`), so it must stay
 * under the small-data threshold or the gp-relative addiu becomes lui/%lo.
 */

extern f32   D_0047DADC;          /* gp - 0x7694 */
extern f32   D_0047DD2C;          /* gp - 0x7444 */
extern void *D_00484920;          /* gp - 0x850  */
extern s32   D_00484928;          /* gp - 0x848  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuConfirmCloseState_520120(void *a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00484920, 0x753C, 0.0f, D_0047DD2C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484920, 0x7544, 1.0f, D_0047DADC, -1.0f);
    }
    normal_ThinkMenuPromptScrollStep_521660(GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0()));
    StateMachineSetState_28ede0(&D_00484928, 0x7532, 0);
    return 1;
}
