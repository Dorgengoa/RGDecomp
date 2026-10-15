#include "types.h"
/* normal 0x005186B0 -- twin of 0x00518660: same five-parameter EABI shape and
 * the same NULL guard, but the gp handle is PASSED to func_290770 rather than
 * only tested, and the shared exit is 0. */

extern void *D_00484710;   /* gp - 0xA60 */

extern f32  func_290770(void *w, u16 id);
extern void func_3768D0(void *a, f32 v);

s32 normal_TransSaveDrawBgCb_5186b0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    if (e != 0) {
        if (D_00484710 != NULL) {
            func_3768D0(a, func_290770(D_00484710, 0x7531));
        }
    }
    return 0;
}
