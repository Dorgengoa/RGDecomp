#include "types.h"

/* insmenu 0x004EF220 (664 bytes, 168 instructions, 27 calls) -- the same page
 * builder as 004F06A0 for a two-flag item: build the icon, write the labels,
 * count the set flag bits and lay the panel out.
 *
 * The bit tests are BITFIELDS: bit 0 is a bare `andi $2, $2, 0x1` and bit 1 is
 * `dsll32 30 / dsrl32 31`.
 *
 * `insmenu_InsectVsListLayoutRows_4ea310`'s third argument reads `h->bit0` OUTSIDE the `h != 0`
 * guard, and that is what retail has -- the null path falls into the same
 * `lbu $2, 0x4($2)`.  Written inside the guard the load moves and the count
 * register changes with it.  Same shape as the store 004F0A00 keeps outside
 * its guard.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
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
extern void func_28F300(const void *a, s32 b, s32 c, s32 d);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_28F590(const void *a, s32 b, s32 c, s32 d);
extern Handle *func_1FEDE0(void);
extern Item *func_430AB0(void *a);
extern void insmenu_InsectVsListLayoutRows_4ea310(s32 a, s32 b, s32 c, s32 d);
extern void func_28F670(const void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void func_28FD10(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);
extern void func_28FCD0(const void *a, s32 b, s32 c, s32 d);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);

void insmenu_InsectVsRegDeletePanelLayout_4ef220(void)
{
    Item *h;
    s32 n;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x53, 0x39, 1.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0x53, 0), 0xB0, 0x28);
    func_290F60(D_004FA180, 0x53, 0x46, 0x50);
    func_290010(D_004FA180, 0x53, 1, -1);
    func_2907A0(D_004FA180, 0x53, 0.0f);
    func_28F510(D_004FA180, 0x55, func_28AA30(D_004842FC, 0x22), 0);
    func_28F300(D_004FA180, 0x55, 0x56, 0);
    func_291110(D_004FA180, 0x32, 0, 1);
    func_291110(D_004FA180, 0x33, 0, 1);
    func_291110(D_004FA180, 0x34, 0, 1);
    func_291110(D_004FA180, 0x35, 0, 1);
    func_28F590(D_004FA180, 0x55, -1, 1);
    h = func_430AB0(func_1FEDE0()->field24);
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        if (h->bit1) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x56, 1, h->bit0, 0x39);
    func_28F670(D_004FA180, 0x56, 0, 0, 0, 0, 0);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x48, 1, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 0, n);
    func_28FD10(D_004FA180, 0x57, 6, 5, 0);
    func_28F930(D_004FA180, 0x57, 0xB0, 0);
    func_28FCD0(D_004FA180, 0x57, -1, 1);
    func_28FCD0(D_004FA180, 0xCA, -1, 0);
    func_28FC30(D_004FA180, 0x54, 0xA4, 0x1C, 0);
    func_290F60(D_004FA180, 0x54, 0, 0);
    func_2907A0(D_004FA180, 0x54, 0.0f);
}
