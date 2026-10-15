#include "types.h"

/* insmenu 0x004F1430 (620 bytes, 156 instructions) -- the two-row page builder with literal label ids.
 * Near-twin of insmenu_InsectVsWatchPanelLayout_4f11d0: same tail, different label bank.
 *
 * `daddiu $17, $0, 0x1` is the unsigned-narrow-type tell (004EA000): the flag
 * is u16 and the two callees take it as u16, or the promotion shows up as an
 * `andi` retail does not have.
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

extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);
extern void func_28F590(const void *a, s32 b, s32 c, s32 d);
extern void func_2911A0(const void *a, u16 b, s32 c);
extern void func_28FCD0(const void *a, s32 b, s32 c, s32 d);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 a, s32 b, f32 t);
extern void *func_28FE10(const void *a, s32 b, s32 c);
extern void func_28BBB0(void *a, s32 b, s32 c);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern Handle *func_1FEDE0(void);
extern Item *func_430B50(void *a);
extern void insmenu_InsectVsListLayoutRows_4ea310(s32 a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsListFrameFit_4ea4e0(s32 a, s32 b, s32 c, u16 d);
extern void insmenu_InsectVsHighlightBarSize_4ea410(s32 a, s32 b, u16 c);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_2907A0(const void *a, s32 b, f32 t);

void insmenu_InsectVsPwBattlePanelLayout_4f1430(void)
{
    s32 i;
    Item *h;
    s32 n;
    u16 wide;

    func_28F510(D_004FA180, 0x22, func_28AA30(D_004842FC, 0xC), 0);
    func_28F510(D_004FA180, 0x22, func_28AA30(D_004842FC, 0x1C), 1);
    func_28F930(D_004FA180, 0x4B, 0x5C, 0);
    for (i = 0; i < 2; i++) {
        func_28F590(D_004FA180, 0x22, 0x3E, i);
        func_2911A0(D_004FA180, i + 0x32, 0x1F);
        func_28FCD0(D_004FA180, 0x4B, 0x20, i);
    }
    func_28F590(D_004FA180, 0x22, -1, 2);
    func_291110(D_004FA180, 0x1F, 1, 1);
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x1F, 0x39, 2.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0x1F, 0), 0xDC, 0x28);
    func_290F60(D_004FA180, 0x1F, 0x34, 0x50);
    h = func_430B50(func_1FEDE0()->field24);
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        if (h->bit1) {
            n++;
        }
    }
    insmenu_InsectVsListLayoutRows_4ea310(0x25, 2, n, 0x39);
    insmenu_InsectVsListLayoutRowWidgets_4ea1b0(0x5E, 3, n);
    insmenu_InsectVsListSetRowColors_4ea110(0x22, 2, n);
    wide = 0;
    if (n == 2) {
        wide = 1;
    }
    insmenu_InsectVsListFrameFit_4ea4e0(0x4A, 0x49, 0xDC, wide);
    insmenu_InsectVsHighlightBarSize_4ea410(0x48, 0xDC, wide);
    func_290F60(D_004FA180, 0x47, 0, 0x72);
    func_28FC30(D_004FA180, 0x21, 0xD0, 0x1C, 0);
    func_290F60(D_004FA180, 0x21, 0, 0);
    func_2907A0(D_004FA180, 0x21, 0.0f);
}
