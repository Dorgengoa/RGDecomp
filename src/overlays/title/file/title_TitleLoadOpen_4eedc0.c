#include "types.h"

/* title.bin overlay, 0x004EEDC0 -- build the LOAD-GAME panel's widget set and
 * drive its two-state fade-out.  Sibling of title_FUN_004EFEB0, which does the
 * same job for OPTIONS; the tail is the identical if/else-if chain on a gp s32
 * (`bnel $3,$0` carrying the NEXT GUARD'S constant, so a chain and not a
 * switch).
 *
 * The five-entry copy at 0x004EEF3C is a HAND-WRITTEN loop, not a struct
 * assignment: two moving cursors and a countdown, with the decrement scheduled
 * between the load and the store.
 *
 * D_0047FAA4 takes the address of a main-image function that splat did not
 * symbolise (the listing shows a bare `lui 0x37 / addiu`).  It has to be a
 * FUNCTION POINTER, not a literal cast: `(void *)0x373E10` compiles to
 * `lui / ORI` because the constant is unsigned, one bit different from
 * retail's `addiu`.  Taking a function's address gives %hi/%lo with a
 * relocation, which is `addiu`.
 */

extern f32 D_0047D518;
extern f32 D_0047D564;
extern f32 D_0047D56C;
extern f32 D_0047D570;
extern s16 D_00480400;
extern void (*D_0047FAA4)(void);
extern void *D_004841E0;
extern void *D_004841E4;
extern void *D_004841E8;
extern s32 D_004841EC;
extern s16 D_004841F0;
extern const u8 D_004F1980;

extern void func_373E10(void);
extern void func_131B60(void *p, s32 v, s32 n);
extern void func_1CF740(void *a, s32 b);
extern void *func_1F5BE0(void);
extern void func_28C190(void *a, s16 *p, s32 c);
extern void func_28EB10(void *a, s32 b);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_28F970(void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_290010(void *a, s32 b, s32 c, s32 d);
extern void func_2905B0(void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);
extern f32 func_290770(void *a, s32 b);
extern void func_2907A0(void *a, s32 b, f32 v);
extern u8 func_290D30(void *a, s32 b);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);
extern void func_290F60(void *a, s32 b, s32 x, s32 y);
extern void func_291110(void *a, s32 b, s32 c, s32 d);
extern void func_377830(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_37BAC0(s32 a);
extern void title_TitleSceneOverlayModeOn_4eaa40(void);
extern void title_TitleLoadFadeWidgets_4eda30(s32 a);
extern void title_TitleLoadProgressWindowShow_4ede10(s32 a, s32 b);
extern void title_TitleLoadHighlightOption_4ede30(s32 a);
extern void title_TitleLoadPortSelectDraw_4ede70(s32 a);
extern void title_TitleLoadSlotListRefreshMaybe_4edeb0(s32 a);
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern void title_TitleSaveSysInit_4ef2b0(void);
extern void title_TitleGetSaveCtx_4ef380(void);
extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);

s32 title_TitleLoadOpen_4eedc0(void *unused, s32 first)
{
    s16 buf[5];
    s16 *src;
    s16 *dst;
    s32 n;

    if (first != 0) {
        title_TitleSceneOverlayModeOn_4eaa40();
        func_290010(D_004841E4, 1, 0, -1);
        func_131B60((void *)&D_004F1980, 0, 0x70);
        title_TitleSaveSysInit_4ef2b0();
        title_TitleGetSaveCtx_4ef380();
        D_0047FAA4 = func_373E10;
        title_TitleLoadProgressWindowShow_4ede10(2, 0);
        D_004841F0 = 0;
        func_291110(D_004841E4, 0xA, 1, 1);
        func_2907A0(D_004841E4, 0xA, 0.0f);
        func_290690(D_004841E4, 0xA, 1.0f, D_0047D564, -1.0f);
        func_290F60(D_004841E4, 0xD, 5, 5);
        func_2905B0(D_004841E4, 0xD, 0.0f, 0.0f, 0.0f, D_0047D56C);
        func_291110(D_004841E4, 7, 1, 1);
        func_2907A0(D_004841E4, 7, 0.0f);
        func_290690(D_004841E4, 7, 1.0f, D_0047D564, -1.0f);
        func_291110(D_004841E4, 0x17, 1, 1);
        func_291110(D_004841E4, 0x18, 1, 1);
        func_291110(D_004841E4, 0x19, 1, 1);
        func_290F60(D_004841E4, 0x19, 0x117, 0x1F);
        src = &D_00480400;
        dst = buf;
        n = 5;
        do {
            n = n - 1;
            *dst = *src;
            src = src + 1;
            dst = dst + 1;
        } while (n > 0);
        func_28C190(D_004841E4, buf, 0);
        func_28F970(D_004841E4, 0x14, 0xC0, 0x12, 0);
        func_290F60(D_004841E4, 0x14, 0x30, 0xF);
        func_290F60(D_004841E4, 0xF, -0x12, 0xC);
        func_290F60(D_004841E4, 0xE, -0xF, 0xF);
        func_2905B0(D_004841E4, 0xE, 0.0f, 0.0f, 0.0f, D_0047D56C);
        func_290F50(D_004841E4, 0xF, 0x5A, 0xC, 0, 0.25f);
        func_290F50(D_004841E4, 0xE, 0x5D, 0xF, 0, 0.25f);
        func_290690(D_004841E4, 0xF, 1.0f, D_0047D564, -1.0f);
        func_290690(D_004841E4, 0xE, D_0047D56C, D_0047D570, -1.0f);
        D_004841EC = 0;
        func_291110(D_004841E4, 0x10, 1, 1);
        func_291110(D_004841E4, 8, 1, 1);
        func_291110(D_004841E4, 0x1B, 1, 1);
        func_291110(D_004841E4, 0x26, 1, 1);
        func_291110(D_004841E4, 0x31, 1, 1);
        func_291110(D_004841E4, 0x43, 0, 1);
        func_290F60(D_004841E4, 8, 0xC8, 0);
        func_290F60(D_004841E4, 0x1B, 0x38, 0x49);
        func_290F60(D_004841E4, 0x26, 0x38, 0xC0);
        func_290F60(D_004841E4, 0x31, 0x38, 0x137);
        func_290F60(D_004841E4, 0x44, 0x1E5, 0x4A);
        func_290F60(D_004841E4, 0x45, 0x1E9, 0x4C);
        title_TitleLoadPortSelectDraw_4ede70(-1);
        title_TitleLoadHighlightOption_4ede30(-1);
        title_TitleLoadSlotListRefreshMaybe_4edeb0(0);
        func_377830(0x45, 0x15B, 3, 0x32, 0);
        title_TitleLoadFadeWidgets_4eda30(0);
        func_2907A0(D_004841E4, 8, 0.0f);
        func_291110(D_004841E4, 0x11, 0, 1);
        func_291110(D_004841E4, 0x12, 0, 1);
        title_TitleLoadShowMsg_4eeb60(-1);
        title_TitleSetNoAnalogPause_4f13b0(0);
    }
    func_37BAC0(0);
    if (D_004841EC == 0) {
        if (!(func_290770(D_004841E4, 7) < 1.0f)) {
            D_004841EC = 1;
            func_290690(D_004841E4, 8, 1.0f, D_0047D564, -1.0f);
            func_290F50(D_004841E4, 8, 0, 0, 0, D_0047D518);
            func_1CF740(func_1F5BE0(), 0xA);
        }
    } else if (D_004841EC == 1) {
        if (func_290D30(D_004841E4, 8) == 0) {
            func_28EB10(D_004841E8, 0x7532);
            func_28EDE0(D_004841E0, 8, 0);
        }
    }
    return 1;
}
