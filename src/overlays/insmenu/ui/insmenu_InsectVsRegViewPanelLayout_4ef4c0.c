#include "types.h"

/* insmenu 0x004EF4C0 (744 bytes, 188 instructions, 30 calls) -- the 004F06A0
 * page builder for the two-row item.  The row loop carries a `break`: retail's
 * `beq $16, $2, .L004EF624` jumps PAST the latch, so it is a break and not an
 * `if` around the two calls that follow.
 *
 * `func_2911A0`/`func_291110`'s row id is u16 -- the `andi $5, $2, 0xFFFF`
 * before each call is the zero-extension the parameter type forces.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

extern const u8 D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

extern void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 a, s32 b, f32 t);
extern void *func_28FE10(const void *a, s32 b, s32 c);
extern void func_28BBB0(void *a, s32 b, s32 c);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_290010(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern void func_28F590(const void *a, s32 b, s32 c, s32 d);
extern void func_2911A0(const void *a, u16 b, s32 c);
extern void func_291110(const void *a, u16 b, s32 c, s32 d);
extern Handle *func_1FEDE0(void);
extern Item *func_430AD0(void *a);
extern void insmenu_InsectVsListLayoutRows_4ea310(s32 a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void func_28FD10(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);
extern void func_28FCD0(const void *a, s32 b, s32 c, s32 d);
extern void func_28F970(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);

void insmenu_InsectVsRegViewPanelLayout_4ef4c0(void)
{
    s32 i;
    Item *h;
    s32 n;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x53, 0x39, 2.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0x53, 0), 0xB0, 0x28);
    func_290F60(D_004FA180, 0x53, 0x46, 0x50);
    func_290010(D_004FA180, 0x53, 1, -1);
    func_2907A0(D_004FA180, 0x53, 0.0f);
    func_28F510(D_004FA180, 0x55, func_28AA30(D_004842FC, 0x15), 0);
    func_28F510(D_004FA180, 0x55, func_28AA30(D_004842FC, 0x17), 1);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            func_28F590(D_004FA180, 0x55, 0x39, i);
        } else {
            func_28F590(D_004FA180, 0x55, 0x22, i);
        }
        if (i == 1) {
            break;
        }
        func_2911A0(D_004FA180, i + 0x32, 0x53);
        func_291110(D_004FA180, i + 0x32, 1, 1);
    }
    func_28F590(D_004FA180, 0x55, -1, 2);
    func_291110(D_004FA180, 0x33, 0, 1);
    h = func_430AD0(func_1FEDE0()->field24);
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x56, 1, n, 0x39);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 2, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 1, n);
    func_28FD10(D_004FA180, 0x57, 6, 0x3E, 0);
    func_28F930(D_004FA180, 0x57, 0x94, 0);
    func_28FCD0(D_004FA180, 0x57, -1, 1);
    func_28FD10(D_004FA180, 0xCA, 0x1C, 5, 0);
    func_28F970(D_004FA180, 0xCA, 0x5C, 0, 0);
    func_28FCD0(D_004FA180, 0xCA, -1, 1);
    func_28FC30(D_004FA180, 0x54, 0xA4, 0x1C, 0);
    func_290F60(D_004FA180, 0x54, 0, 0);
    func_2907A0(D_004FA180, 0x54, 0.0f);
}
