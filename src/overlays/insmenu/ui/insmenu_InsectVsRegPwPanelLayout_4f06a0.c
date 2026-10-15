#include "types.h"

/* insmenu 0x004F06A0 (856 bytes, 216 instructions, 34 calls) -- lay out the
 * four-row page: four label writes off D_004842FC, a three-iteration row loop
 * whose row-kind test is `i < 3`, then the flag count and the rest of the
 * panel geometry.
 *
 * The two flag tests are BITFIELDS (`dsll32 30 / dsrl32 31` is bit 1,
 * `dsll32 29` is bit 2), the same idiom 004F0A00 turns on; an explicit
 * `(x >> 1) & 1` would compile to srl/andi.
 *
 * `func_2911A0`'s second parameter is u16: retail masks the row id with
 * `andi $5, $2, 0xFFFF` before the call, which is the zero-extension a u16
 * parameter forces.  With an s32 parameter the mask is not emitted.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
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
extern Item *func_430B10(void *a);
extern void insmenu_InsectVsListLayoutRows_4ea310(s32 a, s32 b, s32 c, s32 d);
extern void func_28F670(const void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void func_28FD10(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F970(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28FCD0(const void *a, s32 b, s32 c, s32 d);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_2907A0(const void *a, s32 b, f32 t);

void insmenu_InsectVsRegPwPanelLayout_4f06a0(void)
{
    s32 i;
    Item *h;
    s32 n;

    func_28F510(D_004FA180, 0x4E, func_28AA30(D_004842FC, 0x14), 0);
    func_28F510(D_004FA180, 0x4E, func_28AA30(D_004842FC, 0x21), 1);
    func_28F510(D_004FA180, 0x4E, func_28AA30(D_004842FC, 0x17), 2);
    func_28F510(D_004FA180, 0x4E, func_28AA30(D_004842FC, 0x18), 3);
    func_28F300(D_004FA180, 0x4E, 0x56, 0);
    for (i = 1; i < 4; i++) {
        if (i < 3) {
            func_28F590(D_004FA180, 0x4E, 0x39, i);
        } else {
            func_28F590(D_004FA180, 0x4E, 0x22, i);
        }
        func_2911A0(D_004FA180, i + 0x31, 0x4C);
    }
    func_28F590(D_004FA180, 0x22, -1, 4);
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x4C, 0x39, 4.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0x4C, 0), 0xB0, 0x28);
    func_290F60(D_004FA180, 0x4C, 0x46, 0x50);
    func_291110(D_004FA180, 0x4C, 1, 1);
    func_290690(D_004FA180, 0x4C, 1.0f, D_0047D3D8, 0.0f);
    h = func_430B10(func_1FEDE0()->field24);
    n = 1;
    if (h != 0) {
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x4F, 3, n, 0x39);
    func_28F670(D_004FA180, 0x4F, 0, 0, 0, 0, 0);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 4, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x4E, 4, n);
    func_28FD10(D_004FA180, 0xC8, 0x1C, 0x3E, 0);
    func_28F970(D_004FA180, 0xC8, 0x78, 0, 0);
    func_28FD10(D_004FA180, 0xC8, 0x1C, 0x77, 1);
    func_28F970(D_004FA180, 0xC8, 0x94, 0, 1);
    func_28FCD0(D_004FA180, 0xC8, -1, 2);
    func_290F60(D_004FA180, 0x50, 0, 0xAB);
    func_28FC30(D_004FA180, 0x4D, 0xA4, 0x1C, 0);
    func_290F60(D_004FA180, 0x4D, 0, 0);
    func_2907A0(D_004FA180, 0x4D, 0.0f);
}
