#include "types.h"
/* normal 0x00523450 -- the 0x1E-widget phase handler on the STATIC widget
 * D_005281A0 (not a gp handle), same 0x34-Layout family as
 * normal_FUN_0050F960: frame -0x50, Layout at sp+0x10, memset 0x34.
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  Only the guard
 * branches; everything in the block is straight-line.  This member writes
 * Layout f08 (0xAA) and leaves f20..f30 at the memset's zero, so the second
 * word of the pad is a real member here.  `sw $5,0x28($29)` is the scheduler
 * reusing the register that already holds the widget id 0x1E for `f18 = 0x1E`.
 *
 * The tail is UNGUARDED: `c.lt.s $f0,$f1` against an inline 1.0f with a
 * `bc1tl` PAST the call, so the source test is `>= 1.0f` and the call is the
 * fall-through side.  `addiu $4,$28,-0x7C8` is the ADDRESS of the small-data
 * object D_004849A8, not a pointer load.
 */

typedef struct Layout {
    void *f00;
    s32   f04;
    s32   f08;
    s32   f0C;
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

extern u8    D_005281A0[];
extern u8    D_005281C0[];

extern f32   D_0047D7C4;          /* gp - 0x79AC */
extern s32   D_004849A8;          /* gp - 0x7C8  */
extern void *D_004849B4;          /* gp - 0x7BC  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern void *func_15DE80(void);
extern void  func_1451D0(void *a);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_28F3D0(void *w, u16 id, s32 n);
extern void  func_28F510(void *w, u16 id, void *p, s32 n);
extern s32   func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *w, u16 id);
extern void  func_2907A0(void *w, u16 id, f32 x);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_InsectEntryNoFundsMsgOpenState_523450(void *a, s32 b)
{
    Layout lay;

    if (b != 0) {
        func_28F510(D_005281A0, 0x1E, func_28AA30(D_004849B4, 7), 0);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_005281A0, 0x1E, 0);
        lay.f04 = func_28F620(D_005281A0, 0x1E, 0);
        lay.f08 = 0xAA;
        lay.f10 = 0x3B;
        lay.f14 = 0x13;
        lay.f18 = 0x1E;
        lay.f1C = 0xB;
        func_28F3D0(D_005281A0, 0x1E, 0);
        func_1451D0(func_15DE80());
        func_28D0C0(&lay, 0, 0, 0);

        func_291110(D_005281A0, 0x1E, 1, 1);
        func_2907A0(D_005281A0, 0x1E, 0.0f);
        func_290690(D_005281A0, 0x1E, 1.0f, D_0047D7C4, -1.0f);
        func_28EA90(D_005281C0, 0x7532, 1);
    }
    if (func_290770(D_005281A0, 0x1E) >= 1.0f) {
        func_28EDE0(&D_004849A8, 0x7535, 1);
    }
    return 1;
}
