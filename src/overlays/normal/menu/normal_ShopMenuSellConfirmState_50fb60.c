#include "types.h"
/* normal 0x0050FB60 -- the map-screen tick: pumps the 0x4B2570 pad object,
 * reads the panel's mode out of func_28EC60 and drives one of four branches,
 * then re-lays the 0x66 widget from the smoothed scroll value in D_00484678.
 *
 * `ori $5, $0, 0x8000` rather than `addiu` is the pad mask being an UNSIGNED
 * 16-bit constant -- 0x8000 does not fit a signed 16-bit immediate, and that is
 * the source constant, not a cast.
 * The two `sb` stores to D_00484684 sit in their call's delay slot because they
 * are written BEFORE the call in the source, and the stored value is also that
 * call's first argument, which is why `$4` carries both.
 * `D_00484684 * 80 + 0x2C` is the row pitch: mwcc strength-reduces *80 to
 * sll/addu/sll.
 *
 * A NAMED LOCAL FOR THE PRODUCT (`v`) IS THE WHOLE FLOAT STORY, AND IT DOES
 * THREE THINGS AT ONCE.  Written inline as one expression mwcc contracts the
 * product into `adda.s`/`madd.s` (3 words long), picks the IEEE float->int
 * path instead of the R5900 `cvt.w.s`, and puts the sum's operands in the
 * wrong `fs`/`ft` slots -- and the last of those is right length, so only a
 * byte compare sees it.  `#pragma usefloatacc off` and `#pragma fast_fptosi on`
 * each also fix their own symptom, and with `v` named BOTH ARE INERT (measured
 * here by removing them singly and together, still MATCH), so they are not in
 * this file.  levers.d/title-float-const-operand.md's rule says name the
 * LITERAL; the operand that had to be named here is the CALL PRODUCT.
 *
 * `m` is func_28E170's return, NOT func_28EC60's -- the `daddu $16,$2,$0` sits
 * in the NEXT call's delay slot, which reads as the wrong call's result. */

typedef struct Hdl  { u8 pad00[0x14]; s16 f14; } Hdl;
typedef struct Sess { u8 pad00[0x11]; s8  f11; } Sess;

extern const u8 D_004B2570;
extern const u8 D_00527E70;

extern f32   D_0047D3B8;          /* gp - 0x7DB8 */
extern f32   D_0047D3C8;          /* gp - 0x7DA8 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Sess *D_004845D4;          /* gp - 0xB9C  */
extern f32   D_00484678;          /* gp - 0xAF8  */
extern void *D_0048467C;          /* gp - 0xAF4  */
extern s8    D_00484684;          /* gp - 0xAEC  */

extern f32   func_128FD0(f32 x);
extern s32   func_1839F0(const u8 *p, u32 mask);
extern void  func_289EF0(s32 a);
extern void  func_28B630(f32 *p, f32 v);
extern void  func_28D820(const u8 *p, s32 a);
extern s32   func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern Hdl  *func_28EA40(void *p, s32 id);
extern s32   func_28EC60(void *p);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void  func_2A3D90(Sess *s, s32 id);
extern void  func_2A4860(Sess *s, s32 id);
extern void  func_2A4B40(Sess *s, s32 id);
extern void  func_3D4010(void *p, s32 a);
extern void  normal_ShopMenuYesNoHighlight_509270(s32 a, void *p, s32 c);
extern void  normal_ShopMenuMoneyRefresh_50ac80(s32 a, s32 b);
extern void  normal_ShopMenuSellTabsLayout_50e980(s32 a, s32 b);

s32 normal_ShopMenuSellConfirmState_50fb60(void)
{
    s32 m;
    f32 v;

    m = func_28E170(D_004845D0, &D_004B2570, 0, 0);
    func_28EC60(D_004845D0);
    if (m == 1) {
        if (D_00484684 == 0) {
            func_290690(D_004845CC, 0x67, 0.0f, D_0047D3C8, -1.0f);
            func_290690(D_004845CC, 0x57, 0.0f, D_0047D3C8, -1.0f);
            func_290690(D_004845CC, 0x63, 0.0f, D_0047D3C8, -1.0f);
            func_3D4010(D_0048467C, func_28EA40(D_004845D0, 0x7535)->f14);
            normal_ShopMenuMoneyRefresh_50ac80(0x15, 0x14);
            func_28EA40(D_004845D0, 0x7534);
            func_289EF0(0x20);
            normal_ShopMenuSellTabsLayout_50e980(0x38, D_004845D4->f11);
            func_2A4860(D_004845D4, 0x3C);
            func_2A4B40(D_004845D4, 0x3D);
            func_2A3D90(D_004845D4, 0x3E);
            func_28EDE0(D_004845C4, 0x754B, 0);
        } else {
            func_28EDE0(D_004845C4, 0x754A, 0);
        }
    } else if (m == 2) {
        func_289EF0(6);
        func_28EDE0(D_004845C4, 0x754A, 0);
    } else if (func_1839F0(&D_004B2570, 0x8000) != 0) {
        if (D_00484684 == 1) {
            func_289EF0(4);
        }
        D_00484684 = 0;
        normal_ShopMenuYesNoHighlight_509270(0, D_004845CC, 0x65);
    } else if (func_1839F0(&D_004B2570, 0x2000) != 0) {
        if (D_00484684 == 0) {
            func_289EF0(4);
        }
        D_00484684 = 1;
        normal_ShopMenuYesNoHighlight_509270(1, D_004845CC, 0x65);
    }
    func_28B630(&D_00484678, D_0047D3B8);
    v = 8.0f * func_128FD0(D_00484678);
    func_290F50(D_004845CC, 0x66, (s32)(v + (D_00484684 * 80 + 0x2C)),
                0x58, 0, 0.25f);
    func_28D820(&D_00527E70, 0x3F);
    return 1;
}
