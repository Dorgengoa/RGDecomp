#include "types.h"
/* normal 0x005159E0 -- the party-menu per-frame poll.  $4 is never read (the
 * f(void*, s32) handler family); the guard is on the second argument. */

typedef struct Act {
    u8  pad000[0x518];
    f32 f518;
} Act;

extern void *D_004846E8;          /* gp - 0xA88 */
extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern s16   D_0048479C;          /* gp - 0x9D4 */
extern s8    D_00484748;          /* gp - 0xA28 */
extern s8    D_0048472C;          /* gp - 0xA44 */
extern f32   D_0047DA08;          /* gp - 0x7768 */
extern f32   D_0047DA14;          /* gp - 0x775C */

extern Act *func_201A70(void);
extern void func_321E60(Act *p, f32 x);
extern void func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void func_2910A0(void *p, u16 id, s32 *outX, s32 *outY);
extern f32  func_290770(void *p, u16 id);
extern s32  normal_TransMenuTopRowsSlideOut_515b20(s32 a);
extern s32  normal_TransMenuHeaderFadeOut_515cd0(void);

s32 normal_TransMenuCloseState_5159e0(void *a, s32 b)
{
    Act *p;
    f32 t;
    s32 x;
    s32 y;

    p = func_201A70();
    if (b != 0) {
        if (p != 0) {
            func_321E60(p, 15.0f);
        }
        func_290690(D_004846E8, 0x75D1, 0.0f, D_0047DA08, -1.0f);
        D_004806C8 = 2;
        D_0048479C = 0;
        normal_TransMenuTopRowsSlideOut_515b20(0);
        func_290690(D_004846E8, 0x7556, 0.0f, D_0047DA14, -1.0f);
    }
    t = 0.0f;
    if (p != 0) {
        t = p->f518;
    }
    func_2910A0(D_004846E8, 0x753B, &x, &y);
    if (x < -0x49) {
        if (t <= 0.0f && D_0048479C == 0) {
            normal_TransMenuHeaderFadeOut_515cd0();
            D_0048479C = 1;
        }
    }
    if (func_290770(D_004846E8, 0x7532) <= 0.0f) {
        D_00484748 = 0;
        D_0048472C = 1;
    }
    return 1;
}
