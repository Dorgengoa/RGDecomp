#include "types.h"

/* insmenu 0x004EFD90 (828 bytes, 208 instructions, 29 calls) -- the five-row
 * page builder.  The row loop has a three-way row-kind test and a `break` on
 * the last row: retail's `beql $16, $2, .L004EFE60` with $2 = 4 jumps past the
 * latch, which is a break and not an `if`.  The break is also why the loop is
 * entered by `b` to its test instead of being rotated into a do/while the way
 * 004F2C20's constant-bounds loops are.
 *
 * Three bitfields this time: `dsll32 30` is bit 1, `dsll32 29` bit 2,
 * `dsll32 28` bit 3.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

extern const u8 D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */
extern f32 D_0047D3D8;

extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern void func_28F300(const void *a, s32 b, s32 c, s32 d);
extern void func_28F590(const void *a, s32 b, s32 c, s32 d);
extern void func_2911A0(const void *a, u16 b, s32 c);
extern void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 a, s32 b, f32 t);
extern void *func_28FE10(const void *a, s32 b, s32 c);
extern void func_28BBB0(void *a, s32 b, s32 c);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern Handle *func_1FEDE0(void);
extern Item *func_430AF0(void *a);
extern void insmenu_InsectVsListLayoutRows_4ea310(s32 a, s32 b, s32 c, s32 d);
extern void func_28F670(const void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void func_28FD10(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F970(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28FCD0(const void *a, s32 b, s32 c, s32 d);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_2907A0(const void *a, s32 b, f32 t);

void insmenu_InsectVsRegSavePanelLayout_4efd90(void)
{
    s32 i;
    Item *h;
    s32 n;

    for (i = 0; i < 5; i++) {
        func_28F510(D_004FA180, 0x27, func_28AA30(D_004842FC, i + 0x14), i);
        if (i == 0) {
            func_28F300(D_004FA180, 0x27, 0x56, 0);
        } else if (i < 4) {
            func_28F590(D_004FA180, 0x27, 0x39, i);
        } else {
            func_28F590(D_004FA180, 0x27, 0x22, i);
        }
        if (i == 4) {
            break;
        }
        func_2911A0(D_004FA180, i + 0x32, 0x19);
    }
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x19, 0x39, 5.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0x19, 0), 0xB0, 0x28);
    func_290F60(D_004FA180, 0x19, 0x46, 0x3C);
    func_291110(D_004FA180, 0x19, 1, 1);
    func_290690(D_004FA180, 0x19, 1.0f, D_0047D3D8, 0.0f);
    h = func_430AF0(func_1FEDE0()->field24);
    n = 1;
    if (h != 0) {
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
        if (h->bit3) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x28, 4, n, 0x39);
    func_28F670(D_004FA180, 0x28, 0, 0, 0, 0, 0);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 5, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x27, 5, n);
    func_28FD10(D_004FA180, 0xC9, 0x1C, 0x3E, 0);
    func_28F970(D_004FA180, 0xC9, 0x5C, 0, 0);
    func_28FD10(D_004FA180, 0xC9, 0x1C, 0x77, 1);
    func_28F970(D_004FA180, 0xC9, 0x120, 0, 1);
    func_28FD10(D_004FA180, 0xC9, 0x1C, 0xB0, 2);
    func_28F970(D_004FA180, 0xC9, 0x94, 0, 2);
    func_28FCD0(D_004FA180, 0xC9, -1, 3);
    func_290F60(D_004FA180, 0x52, 0, 0xE4);
    func_28FC30(D_004FA180, 0x26, 0xA4, 0x1C, 0);
    func_290F60(D_004FA180, 0x26, 0, 0);
    func_2907A0(D_004FA180, 0x26, 0.0f);
}
