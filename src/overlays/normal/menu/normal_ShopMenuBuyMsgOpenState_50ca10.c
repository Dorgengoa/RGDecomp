#include "types.h"
/* normal 0x0050CA10 -- sibling of normal_FUN_0050F960 (same 0x70 widget phase
 * handler family, f(void *, s32), `$4` never read, guard on `b`, returns 1).
 *
 * Differences from the seed, all of them local:
 *   - the colour argument is selected by the gp flag D_00484630: the
 *     FALL-THROUGH arm of the `bnel` is 0xFF303030, so the test is `== 0`.
 *   - the same gp byte is the string id for func_28AA30 -- it is read INLINE
 *     a second time (two `lbu -0xB40($28)`), not hoisted into a local.
 *   - no measured-width centring step (no func_28F400 / func_28F590).
 *   - the 0x34 Layout carries a different box; every value is non-zero so
 *     there are no zero stores for the scheduler to use as filler and the
 *     addiu/sw pairs sit adjacent in strict address order.
 *   - the tail has no func_28D820 and posts 0x753F.
 */

typedef struct Layout {
    void *f00;
    s32   f04;
    u8    pad08[8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    s32   f2C;
    s16   f30;
} Layout;

extern f32   D_0047D460;          /* gp - 0x7D10 */
extern u8    D_00484630;          /* gp - 0xB40  */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern void *D_004845F8;          /* gp - 0xB78  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_28F510(void *w, u16 id, void *p, s32 n);
extern s32   func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290A40(void *w, u16 id, u32 rgba, s32 n);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_ShopMenuBuyMsgOpenState_50ca10(void *a, s32 b)
{
    Layout lay;

    if (b != 0) {
        func_291110(D_004845CC, 0x70, 1, 1);
        func_290690(D_004845CC, 0x70, 1.0f, D_0047D460, 0.0f);
        func_290A40(D_004845CC, 0x70,
                    D_00484630 == 0 ? 0xFF303030 : 0xFF001030, 0);
        func_28F510(D_004845CC, 0x70, func_28AA30(D_004845F8, D_00484630), 0);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_004845CC, 0x70, 0);
        lay.f04 = func_28F620(D_004845CC, 0x70, 0);
        lay.f10 = 0x3C;
        lay.f14 = 0xC;
        lay.f18 = 0x1C;
        lay.f1C = 8;
        lay.f20 = 0x46;
        lay.f24 = 0x4A;
        lay.f28 = 0x196;
        lay.f2C = 0x104;
        lay.f30 = 4;
        func_28D0C0(&lay, 0, 0, 0);

        func_28EA90(D_004845D0, 0x7536, 0);
    }
    func_28EDE0(D_004845C4, 0x753F, 0);
    return 1;
}
