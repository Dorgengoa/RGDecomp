#include "types.h"
/* normal 0x0051C1E0 -- two-state phase driver on the gp word D_00484884.
 * Same shape as normal_FUN_0051A1A0 (which drives the same states off a
 * pointer argument instead of a gp word).
 */

extern void *D_00484710;          /* gp - 0xA60 */
extern s32   D_00484884;          /* gp - 0x8EC */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047D9E0;          /* gp - 0x7790 */
extern f32   D_0047D9E4;          /* gp - 0x778C */

extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern f32   func_290770(void *w, u16 id);
extern void  func_2910A0(void *w, u16 id, s32 *outX, s32 *outY);
extern void  func_28F930(void *w, u16 id, s32 a, s32 b);

s32 normal_TransWarpCloseSlide_51c1e0(void)
{
    s32 x;
    s32 y;

    switch (D_00484884) {
    case 0:
        func_290F50(D_00484710, 0x753C, -0x12, 0x9C, 0, D_0047D5D0);
        func_290F50(D_00484710, 0x7537, -0xF, 0x9F, 0, D_0047D5D0);
        func_2910A0(D_00484710, 0x753C, &x, &y);
        if (x < 0x1F) {
            D_00484884 = 1;
            func_290690(D_00484710, 0x7553, 0.0f, D_0047D9E0, -1.0f);
        }
        break;
    case 1:
        func_290770(D_00484710, 0x7553);
        func_290690(D_00484710, 0x7550, 1.0f, D_0047D9E4, -1.0f);
        func_28F930(D_00484710, 0x7550, 0xE0, 0);
        D_00484884 = 4;
        break;
    }
    return 0;
}
