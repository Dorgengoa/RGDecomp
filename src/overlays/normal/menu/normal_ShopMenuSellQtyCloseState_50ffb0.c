#include "types.h"
/* normal 0x0050FFB0 -- the four-widget POSE list, same shape as the tail of
 * normal_FUN_0050F880: f(void *, s32), `$4` never read, guard on `b`, returns 1.
 *
 * Four func_290690 calls in a row, the first on the D_004845C8 handle and the
 * other three on D_004845CC.  The first is 1.0f / gp literal / -1.0f, the other
 * three are 0.0f / a different gp literal / -1.0f -- the 0.0f is materialised
 * once (`mtc1 $0,$f12`) per call, not hoisted, and -1.0f is re-materialised by
 * `lui 0xBF80` every time.  Tail posts 0x7543 through func_28EDE0.
 */

extern f32   D_0047D4A8;          /* gp - 0x7CC8 */
extern f32   D_0047D4AC;          /* gp - 0x7CC4 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845C8;          /* gp - 0xBA8  */
extern void *D_004845CC;          /* gp - 0xBA4  */

extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

s32 normal_ShopMenuSellQtyCloseState_50ffb0(void *a, s32 b)
{
    if (b != 0) {
        func_290690(D_004845C8, 0x40, 1.0f, D_0047D4A8, -1.0f);
        func_290690(D_004845CC, 0x48, 0.0f, D_0047D4AC, -1.0f);
        func_290690(D_004845CC, 0x57, 0.0f, D_0047D4AC, -1.0f);
        func_290690(D_004845CC, 0x67, 0.0f, D_0047D4AC, -1.0f);
    }
    func_28EDE0(D_004845C4, 0x7543, 0);
    return 1;
}
