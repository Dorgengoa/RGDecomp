#include "types.h"
/* normal 0x0051A1A0 -- two-state phase driver, state word behind the pointer
 * argument.  Sibling of normal_FUN_0051C1E0. */

extern void *D_004847D4;          /* gp - 0x99C */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047D9F8;          /* gp - 0x7778 */
extern f32   D_0047DA00;          /* gp - 0x7770 */

extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern f32   func_290770(void *w, u16 id);
extern void  func_2910A0(void *w, u16 id, s32 *outX, s32 *outY);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern void  func_28F930(void *w, u16 id, s32 a, s32 b);

s32 normal_TransSaveCloseSlide_51a1a0(s32 *p)
{
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    switch (p[0]) {
    case 0:
        func_290F50(D_004847D4, 0x753B, -0x12, 0xC, 0, D_0047D5D0);
        func_290F50(D_004847D4, 0x7536, -0xF, 0xF, 0, D_0047D5D0);
        func_290690(D_004847D4, 0x7558, 0.0f, D_0047D9F8, -1.0f);
        func_290F50(D_004847D4, 0x7558, 0xC8, 0, 0, D_0047D5D0);
        func_2910A0(D_004847D4, 0x753B, &x, &y);
        if (x < 0x1F) {
            p[0] = 1;
            func_290690(D_004847D4, 0x7553, 0.0f, -0.05f, -1.0f);
            func_290690(D_004847D4, 0x7531, 0.0f, -0.05f, -1.0f);
        }
        break;
    case 1:
        func_290770(D_004847D4, 0x7553);
        func_290690(D_004847D4, 0x754F, 1.0f, D_0047DA00, -1.0f);
        func_28F930(D_004847D4, 0x754F, 0xE0, 0);
        func_2910A0(D_004847D4, 0x753B, &x2, &y2);
        if (x2 == -0x12) {
            if (y2 == 0xC) {
                func_290F60(D_004847D4, 0x753B, -0x4A, 0x4F);
                func_290F60(D_004847D4, 0x7536, -0x45, 0x53);
            }
        }
        p[0] = 3;
        break;
    }
    return 0;
}
