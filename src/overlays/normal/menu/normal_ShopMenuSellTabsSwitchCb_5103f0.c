#include "types.h"

typedef struct P3F0S {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} P3F0S;

typedef struct P3F0G {
    u8 pad00[0x10];
    s8 f10;
    s8 f11;
} P3F0G;

typedef struct P3F0C {
    u8    pad00[0x18];
    void *f18;
} P3F0C;

extern f32    D_0047D240;         /* gp - 0x7F30 */
extern P3F0G *D_004845D4;         /* gp - 0xB9C  */
extern void  *D_004845A8;         /* gp - 0xBC8  */
extern s32    D_00484680;         /* gp - 0xAF0  */
extern u8     D_004B2570[];

extern s32    func_1839F0(u8 *pad, s32 mask);
extern s32    func_183DD0(u8 *pad, s32 mask);
extern void   normal_ShopMenuSellTabsLayout_50e980(s32 a, s32 b);
extern void   func_2A4860(void *p, s32 a);
extern void   func_2A4B40(void *p, s32 a);
extern void   func_2A3D90(void *p, s32 a);
extern P3F0C *func_1FEDE0(void);
extern P3F0C *func_3C86E0(void *ctx, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void   normal_ShopMenuItemInfoShow_509520(P3F0C *c, s32 a, s32 b, s32 c2, s32 d, f32 f);
extern void   func_1B9520(void *p, s32 a, s32 b, f32 f);
extern void   normal_ShopMenuSellCellHintShow_50f650(s32 a);

s32 normal_ShopMenuSellTabsSwitchCb_5103f0(P3F0S *a)
{
    P3F0C *ctx;
    s32    max;
    u8    *pad;
    s32    cur;
    s32    ok;

    pad = D_004B2570;
    cur = D_004845D4->f11;
    max = D_004845D4->f10;
    ok = 0;
    if (func_1839F0(pad, 4) != 0) {
        if (cur > 0) {
            cur--;
            ok = 1;
        } else if (func_183DD0(pad, 4) == 0) {
            cur = max - 1;
            ok = 1;
        }
    } else if (func_1839F0(pad, 8) != 0) {
        if (cur < max - 1) {
            cur++;
            ok = 1;
        } else if (func_183DD0(pad, 8) == 0) {
            cur = 0;
            ok = 1;
        }
    }
    if (ok != 0) {
        D_004845D4->f11 = cur;
        normal_ShopMenuSellTabsLayout_50e980(0x38, cur);
        func_2A4860(D_004845D4, 0x3C);
        func_2A4B40(D_004845D4, 0x3D);
        func_2A3D90(D_004845D4, 0x3E);
        ctx = func_1FEDE0();
        normal_ShopMenuItemInfoShow_509520(func_3C86E0(ctx->f18, 0, cur, a->f10, a->f12, 0),
                            0x34, 0x33, 0x57, 0x15E, D_0047D240);
        func_1B9520(D_004845A8, 0xB, 0, 1.0f);
        D_00484680 = 0;
        normal_ShopMenuSellCellHintShow_50f650(0);
    }
    return 1;
}
