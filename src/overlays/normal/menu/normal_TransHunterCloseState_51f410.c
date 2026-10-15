#include "types.h"
/* normal 0x0051F410 */

extern void *D_00484710;          /* gp - 0xA60 */
extern void *D_0048470C;          /* gp - 0xA64 */
extern s8    D_0048472C;          /* gp - 0xA44 */
extern s32   D_004848C4;          /* gp - 0x8AC */
extern f32   D_0047D4B0;          /* gp - 0x7CC0, 0.08f  */
extern f32   D_0047D9C0;          /* gp - 0x77B0, -0.1f  */

extern void func_290E00(void *w, u16 id, s32 a, s32 b, s32 c, f32 x, f32 y);
extern void func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void func_2910A0(void *w, u16 id, s32 *x, s32 *y);
extern void func_290F60(void *w, u16 id, s32 x, s32 y);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern s32  normal_TransHunterCloseSlide_51f550(void);
extern void normal_TransMenuSubResFree_517cf0(void);

s32 normal_TransHunterCloseState_51f410(void *a, s32 b)
{
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    if (b != 0) {
        func_290E00(D_00484710, 0x7633, 0x200, 0x49, 3, D_0047D4B0, 0.0f);
        func_290690(D_00484710, 0x7633, 0.0f, -0.0625f, 1.0f);
        func_290690(D_00484710, 0x764B, 0.0f, D_0047D9C0, -1.0f);
        D_004848C4 = 0;
    }
    normal_TransHunterCloseSlide_51f550();
    func_2910A0(D_00484710, 0x753D, &x, &y);
    if (x == -0x12) {
        if (y == 0xC) {
            func_290F60(D_00484710, 0x753D, -0x4A, 0x9B);
            func_290F60(D_00484710, 0x7538, -0x45, 0x9F);
        }
    }
    if (D_004848C4 == 4) {
        func_2910A0(D_00484710, 0x753D, &x2, &y2);
        if (x2 == -0x4A) {
            D_0048472C = 1;
            func_28EDE0(D_0048470C, 3, 0);
        }
        normal_TransMenuSubResFree_517cf0();
    }
    return 1;
}
