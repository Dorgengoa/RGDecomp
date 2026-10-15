#include "types.h"

/* insmenu 0x004F1C80 (756 bytes, 192 instructions, 27 calls) -- the three-row
 * page builder with the two-slot sub-row pass.
 *
 * `daddiu $16, $0, 0x1` is the UNSIGNED-NARROW-TYPE tell recorded for
 * 004EA000: an `s32` local gives `addiu`.  The flag is `u16`, and the two
 * callees have to take it as `u16` as well -- with an `s32` parameter the
 * promotion is a zero-extending `andi` that retail does not have.  Other
 * callers of insmenu_InsectVsHighlightBarSize_4ea410 declare it (s32, s32, s32); those pass
 * literals, where the type leaves no trace.
 *
 * `it->field4C6[j]` is a real array member: retail computes `addu $2, $16, $18`
 * and folds 0x4C6 into the `lbu`'s immediate, which is what an array indexed
 * by a variable gives.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 pad05[0x4C1];
    u8 field4C6[2];
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

extern const u8 D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern void func_28F590(const void *a, s32 b, s32 c, s32 d);
extern void func_2911A0(const void *a, u16 b, s32 c);
extern void func_28FCD0(const void *a, s32 b, s32 c, s32 d);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 a, s32 b, f32 t);
extern void *func_28FE10(const void *a, s32 b, s32 c);
extern void func_28BBB0(void *a, s32 b, s32 c);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern Handle *func_1FEDE0(void);
extern Item *func_430B70(void *a);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsListLayoutRows_4ea310(s32 a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListFrameFit_4ea4e0(s32 a, s32 b, s32 c, u16 d);
extern void insmenu_InsectVsHighlightBarSize_4ea410(s32 a, s32 b, u16 c);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);

void insmenu_InsectVsTwoPlayerPanelLayout_4f1c80(void)
{
    s32 i;
    Item *it;
    s32 n;
    s32 j;
    u16 wide;

    for (i = 0; i < 3; i++) {
        func_28F510(D_004FA180, 0x1B, func_28AA30(D_004842FC, i + 0xB), i);
        func_28F590(D_004FA180, 0x1B, 0x3E, i);
        func_2911A0(D_004FA180, i + 0x32, 0x11);
        func_28FCD0(D_004FA180, 0x12, 0x20, i);
    }
    func_28F590(D_004FA180, 0x1B, -1, 3);
    func_291110(D_004FA180, 0x11, 1, 1);
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x11, 0x39, 3.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0x11, 0), 0xDC, 0x28);
    func_290F60(D_004FA180, 0x3F, 0x34, 0x50);
    it = func_430B70(func_1FEDE0()->field24);
    n = 0;
    if (it != 0) {
        if (it->bit0) {
            n++;
            func_2907A0(D_004FA180, 0x45, 1.0f);
            func_290F60(D_004FA180, 0x45, 0xD4, 0);
            for (j = 0; j < 2; j++) {
                if (it->field4C6[j] == 0) {
                    func_28F930(D_004FA180, 0x46, 0xE8, j + 1);
                } else {
                    func_28F930(D_004FA180, 0x46, 0x104, j + 1);
                }
            }
        } else {
            func_2907A0(D_004FA180, 0x45, 0.0f);
        }
        if (it->bit1) {
            n++;
        }
        if (it->bit2) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x24, 3, n, 0x39);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x5E, 4, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 3, n);
    wide = 0;
    if (n == 3) {
        wide = 1;
    }
    insmenu_InsectVsListFrameFit_4ea4e0(0x41, 0x43, 0xDC, wide);
    insmenu_InsectVsHighlightBarSize_4ea410(0x42, 0xDC, wide);
    func_290F60(D_004FA180, 0x40, 0, 0xAB);
    func_28FC30(D_004FA180, 0x13, 0xD0, 0x1C, 0);
    func_290F60(D_004FA180, 0x13, 0, 0);
    func_2907A0(D_004FA180, 0x13, 0.0f);
}
