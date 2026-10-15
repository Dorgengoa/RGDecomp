#include "types.h"

/* insmenu 0x004F2C20 (548 bytes, 140 instructions, 23 calls) -- build the two
 * icons and fill the two label banks.  Three constant-bounds `for` loops, all
 * of which mwcc emits as do/while with no entry guard; the loop header's first
 * instruction (`lw $4, -0xE74($28)`) is hoisted above the loop and duplicated
 * into the `bnel`'s delay slot, which is ordinary rotation and not a second
 * read to write.
 */

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
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);

void insmenu_InsectVsTopPanelLayout_4f2c20(void)
{
    s32 i;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(3, 0x2B, 4.0f);
    func_28BBB0(func_28FE10(D_004FA180, 3, 0), 0x132, 0x2B);
    func_290F60(D_004FA180, 1, 0x26, 0x50);
    func_28BBB0(func_28FE10(D_004FA180, 0x36, 0), 0x82, 0x2B);
    func_290F60(D_004FA180, 0x36, 0, 0xAC);
    func_290010(D_004FA180, 1, 1, -1);
    func_2907A0(D_004FA180, 1, 0.0f);
    for (i = 0; i < 5; i++) {
        func_28F510(D_004FA180, 0x37, func_28AA30(D_004842FC, i), i);
        func_28F590(D_004FA180, 0x37, 0xA, i);
    }
    for (i = 0; i < 2; i++) {
        func_28F510(D_004FA180, 0x38, func_28AA30(D_004842FC, 0x23), i);
    }
    func_28F510(D_004FA180, 0x38, func_28AA30(D_004842FC, 0x25), 2);
    func_28F510(D_004FA180, 0x38, func_28AA30(D_004842FC, 0x24), 3);
    for (i = 0; i < 2; i++) {
        func_28F510(D_004FA180, 0x38, func_28AA30(D_004842FC, 0x25), i + 4);
    }
    func_28FC30(D_004FA180, 2, 0x126, 0x1F, 0);
    func_290F60(D_004FA180, 2, 0, 0);
    func_2907A0(D_004FA180, 2, 0.0f);
}
