#include "types.h"
/* normal 0x0051DCD0 -- f(void *, s32) state handler and twin of
 * normal_FUN_0051D3C0: on `b != 0` it starts the 0x763F panel's slide through
 * func_290E00, colours it through func_290690 and clears the D_0048477C flag;
 * every call posts event 0x12 and returns 1.
 *
 * func_290E00 takes FIVE integer arguments -- the fifth reaches $8, which is
 * the EABI, not o32.  `lui 0xBD800000 / mtc1 $2,$f13` is -0.0625f inline.
 */

extern f32   D_0047D4B0;          /* gp - 0x7CC0 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern u8    D_0048477C;          /* gp - 0x9F4  */

extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void func_290E00(void *p, u16 id, f32 x, f32 y, s32 c, s32 d, s32 e);

s32 normal_TransHunterRankCloseState_51dcd0(void *a, s32 b)
{
    if (b != 0) {
        func_290E00(D_00484710, 0x763F, D_0047D4B0, 0.0f, 0x200, 0x49, 3);
        func_290690(D_00484710, 0x763F, 0.0f, -0.0625f, 1.0f);
        D_0048477C = 0;
    }
    func_28EDE0(D_0048470C, 0x12, 0);
    return 1;
}
