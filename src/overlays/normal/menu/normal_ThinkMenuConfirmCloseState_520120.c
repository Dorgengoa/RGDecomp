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

extern f32   func_1CEBA0(s32 a);
extern s32   func_1F5BE0(void);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  normal_ThinkMenuPromptScrollStep_521660(f32 x);

s32 normal_ThinkMenuConfirmCloseState_520120(void *a, s32 b)
{
    if (b != 0) {
        func_290690(D_00484920, 0x753C, 0.0f, D_0047DD2C, -1.0f);
        func_290690(D_00484920, 0x7544, 1.0f, D_0047DADC, -1.0f);
    }
    normal_ThinkMenuPromptScrollStep_521660(func_1CEBA0(func_1F5BE0()));
    func_28EDE0(&D_00484928, 0x7532, 0);
    return 1;
}
