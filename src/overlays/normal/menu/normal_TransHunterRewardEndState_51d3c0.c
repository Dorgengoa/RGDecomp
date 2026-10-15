#include "types.h"
/* normal 0x0051D3C0 -- f(void *, s32) state handler: on `b != 0` it fades the
 * 0x791B panel out and the 0x764A panel in, then posts event 0x1B on every
 * call and returns 1.  Twin of normal_FUN_0051DCD0.
 *
 * `lui 0x3F80 / mtc1` is 1.0f inline and `lui 0xBF80 / mtc1` is -1.0f inline;
 * only the middle float argument is a gp pool literal.  `$4` is never read.
 */

extern f32   D_0047D9B0;          /* gp - 0x77C0 */
extern f32   D_0047D9B4;          /* gp - 0x77BC */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_00484718;          /* gp - 0xA58  */

extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_290690(void *p, u16 id, f32 x, f32 y, f32 z);

s32 normal_TransHunterRewardEndState_51d3c0(void *a, s32 b)
{
    if (b != 0) {
        func_290690(D_00484718, 0x791B, 0.0f, D_0047D9B0, -1.0f);
        func_290690(D_00484710, 0x764A, 1.0f, D_0047D9B4, -1.0f);
    }
    func_28EDE0(D_0048470C, 0x1B, 0);
    return 1;
}
