#include "types.h"
/* normal 0x0050F960 -- the 0x70 widget's phase handler: on `b != 0` it turns
 * the widget on, sets its colour/alpha, gives it the id-5 string, centres it
 * horizontally from its own measured width and lays out the 0x34-byte box.
 * Both paths then re-arm the D_00527E70 layout and post 0x754C.
 *
 * `$4` is never read -- the f(void *, s32) state-handler family (the same
 * shape as normal_FUN_0050C730); the guard is on `b` and every path returns 1.
 * `bgez $2 / sra $3,$2,1` with the +1 bias is a signed `/ 2`.
 * `lui 0x3F80 / mtc1` is 1.0f materialised inline (low half zero); the middle
 * float argument comes from gp and is the shared literal D_0047D460.
 * The Layout stores are in ADDRESS order in the source -- the two zero stores
 * that appear out of place in the listing are the scheduler using them as the
 * filler between each `addiu` and its `sw`.
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

extern const u8 D_00527E70;

extern f32   D_0047D460;          /* gp - 0x7D10 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern void *D_004845F8;          /* gp - 0xB78  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern void  func_28D820(const u8 *p, s32 a);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s32   func_28F400(void *w, u16 id, s32 n);
extern void  func_28F510(void *w, u16 id, void *p, s32 n);
extern void  func_28F590(void *w, u16 id, s32 a, s32 n);
extern s32   func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290A40(void *w, u16 id, u32 rgba, s32 n);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_ShopMenuSellMsgOpenState_50f960(void *a, s32 b)
{
    Layout lay;

    if (b != 0) {
        func_291110(D_004845CC, 0x70, 1, 1);
        func_290690(D_004845CC, 0x70, 1.0f, D_0047D460, 0.0f);
        func_290A40(D_004845CC, 0x70, 0xFF303030, 0);
        func_28F510(D_004845CC, 0x70, func_28AA30(D_004845F8, 5), 0);
        func_28F590(D_004845CC, 0x70, 0x67 - func_28F400(D_004845CC, 0x70, 0) / 2, 0);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_004845CC, 0x70, 0);
        lay.f04 = func_28F620(D_004845CC, 0x70, 0);
        lay.f10 = 0x3C;
        lay.f14 = 0xC;
        lay.f18 = 0x1C;
        lay.f1C = 8;
        lay.f20 = 0;
        lay.f24 = 0;
        lay.f28 = 0x200;
        lay.f2C = 0x1C0;
        lay.f30 = 4;
        func_28D0C0(&lay, 0, 0, 0);

        func_28EA90(D_004845D0, 0x7536, 0);
    }
    func_28D820(&D_00527E70, 0x3F);
    func_28EDE0(D_004845C4, 0x754C, 0);
    return 1;
}
