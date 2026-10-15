#include "types.h"
/* normal 0x0051EA30 -- twin of normal_FUN_0051E510, shorter tail. */

extern void *D_0048470C;          /* gp - 0xA64 */
extern void *D_00484718;          /* gp - 0xA58 */
extern u16   D_004848C0;          /* gp - 0x8B0 */
extern f32   D_0047D9C0;          /* gp - 0x77B0 */

extern void  func_2072F0(s32 a, f32 t);
extern s32   func_2072C0(void);
extern f32   func_207290(void);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_28EDE0(void *w, u16 id, s32 a);

s32 normal_TransHunterVoiceEndState_51ea30(void *a, s32 b)
{
    s32 st;
    f32 t;

    if (b != 0) {
        func_2072F0(0xF, 0.0f);
        func_290690(D_00484718, 0x7919, 0.0f, D_0047D9C0, -1.0f);
    }
    st = func_2072C0();
    t = func_207290();
    if (st == -2 || st == 0 || st == 2 || t <= 0.0f) {
        func_28EDE0(D_0048470C, D_004848C0, 0);
    }
    return 1;
}
