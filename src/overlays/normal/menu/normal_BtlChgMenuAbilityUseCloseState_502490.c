#include "types.h"
/* normal 0x00502490 -- the shutter-countdown sibling of
 * normal_FUN_005023B0 on the same gp handle D_0048449C.  The gp byte
 * D_00480520 is the counter: while it is > 0 the frame just steps the
 * scroller and decrements, returning 0; at 0 it re-arms the widgets and
 * reloads the counter with 6 and returns 1.
 *
 * `bgtzl` carries the D_004844A0 load for func_28EC60 in its delay slot --
 * the branch-likely slot IS the taken path's first argument setup.
 * The trailing `addiu $3,$0,6` appears twice (once in a delay slot); it is
 * ONE source store written after the if.
 */

typedef struct Obj { u8 pad000[0x456]; u8 f456; } Obj;

extern f32   D_0047D278;          /* gp - 0x7EF8 */
extern u8    D_00480520;          /* gp - 0x4C50 */
extern Obj  *D_00484454;          /* gp - 0xD1C  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */

extern void  normal_BtlChgMenuPanelGlowMaybe_4faf20(s32 a, s32 b);
extern void  normal_BtlChgMenuCursorShow_503730(s32 a);
extern void  normal_BtlChgMenuCursorBob_503750(s32 a, s32 b, s32 c, s32 d);
extern void  normal_BtlChgPageGetCursorPos_505df0(Obj *p, s32 *x, s32 *y);
extern s32   normal_BtlChgPageGetCloseCode_505fb0(Obj *p);
extern void  normal_BtlChgPageSetCloseCode_505fc0(Obj *p, s32 a);
extern void  normal_BtlChgPageStop_505fd0(Obj *p);
extern s32   func_28EC60(void *p);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_BtlChgMenuAbilityUseCloseState_502490(void *a, s32 b)
{
    s32 x;
    s32 y;
    s32 h;

    if (D_00480520 <= 0) {
        func_290F50(D_0048449C, 1, 0x15E, 0x147, 0, D_0047D278);
        func_290690(D_0048449C, 1, 0.0f, 0.125f, 1.0f);
        func_290F50(D_0048449C, 0x40, 0x15E, 0x143, 0, D_0047D278);
        normal_BtlChgPageStop_505fd0(D_00484454);
        normal_BtlChgMenuCursorShow_503730(0);
        D_00484454->f456 = 0;
        if (normal_BtlChgPageGetCloseCode_505fb0(D_00484454) != 0) {
            normal_BtlChgMenuPanelGlowMaybe_4faf20(-1, 1);
            normal_BtlChgPageSetCloseCode_505fc0(D_00484454, 2);
        }
        D_00480520 = 6;
        return 1;
    }
    h = func_28EC60(D_004844A0);
    normal_BtlChgPageGetCursorPos_505df0(D_00484454, &x, &y);
    normal_BtlChgMenuCursorBob_503750(h, 0, x - 0x20, y + 5);
    D_00480520 = D_00480520 - 1;
    return 0;
}
