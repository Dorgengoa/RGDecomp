#include "types.h"

/* factory.bin overlay, 0x004EA870 -- lay out the factory result banner.
 *
 * 280 instructions, 43 calls, 4 conditional branches.
 *
 * ★★★ THE `r - 0x13A` EXPRESSION IS WRITTEN OUT AT ALL FOUR STORE SITES, NOT
 * HELD IN A LOCAL.  Retail issues `addiu $3, $16, -0x13A` fresh before each of
 * the four `sh`s.  That is the opposite of what 0x004F7ED0 does with its own
 * shared value, and the discriminator is the COST: one `addiu` is cheaper to
 * recompute than to keep live, a two-instruction expression is not.
 *
 * ★ `lw $19, -0x498C($28)` happens EXACTLY ONCE and lives in a callee-saved
 * register across the whole function, so the gp global is a named local here --
 * the mirror of 0x004EA1D0, where every use is separated by a call and retail
 * re-reads.  Count the loads in the reference before choosing.
 *
 * ★ `sra` under `bgez` with a +1 bias is a signed `/ 2`, three times.
 * ★ `ori $5, $0, 0x88C2` is just a literal too big for a signed 16-bit
 * immediate; `lui 0x3F80` / `mtc1` is a float constant materialised inline
 * because its low half is zero.
 */

typedef struct Layout {
    void *f0;
    s32   f4;
    s32   f8;
    u8    padC[4];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    u8    pad20[0x10];
    s16   f30;
} Layout;

typedef struct Glyph {
    u8  pad0[4];
    s16 f4;
    s16 f6;
    s16 f8;
} Glyph;

typedef struct Row {
    u8  pad0[0x18];
    s16 f18;
} Row;

typedef struct Scene {
    u8    pad0[0x68];
    void *f68;
    u8    pad6C[0xC];
    u8    f78;
} Scene;

extern void  *D_004807E4;
extern void  *D_004807EC;
extern Scene *D_00484A44;
extern void  *D_00484A70;
extern u8     D_00484A84;

extern void  factory_FactoryMenuBannerSetStyle_4eae00(s32 a);
extern void  factory_FactoryMenuCursorBob_4f0f30(Scene *s, s32 a);
extern void  func_131B60(void *p, s32 v, s32 n);
extern s32   func_1451D0(s32 a);
extern s32   func_15DE80(void);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern Glyph *func_28EA40(void *ctx, s32 id);
extern void  func_28EA90(void *ctx, s32 id, s32 a);
extern void  func_28F300(void *ctx, s32 id, s32 x, s32 n);
extern s32   func_28F3D0(void *ctx, s32 id, s32 a);
extern s32   func_28F400(void *ctx, s32 id, s32 a);
extern void  func_28F510(void *ctx, s32 id, void *p, s32 n);
extern void  func_28F550(void *ctx, s32 id, s32 y, s32 n);
extern s32   func_28F620(void *ctx, s32 id, s32 a);
extern void  func_28FD10(void *ctx, s32 id, s32 x, s32 y, s32 n);
extern void  func_28FD70(void *ctx, s32 id, s32 x, s32 y, s32 w, s32 h, s32 n);
extern Row  *func_28FE10(void *ctx, s32 id, s32 n);
extern void  func_290010(void *ctx, s32 id, s32 a, s32 b);
extern void  func_290690(void *ctx, s32 id, f32 a, f32 b, f32 c);
extern void  func_290F60(void *ctx, s32 id, s32 x, s32 y);
extern void  func_291110(void *ctx, s32 id, s32 a, s32 b);

void factory_FactoryMenuQuitConfirmOpen_4ea870(void)
{
    Layout lay;
    Glyph *g;
    Row *row;
    void *w;
    s32 cw;
    s32 ch;
    s32 y;
    s32 r;

    factory_FactoryMenuBannerSetStyle_4eae00(1);
    w = D_004807E4;
    func_28EA90(D_00484A44->f68, 0x88C2, 1);
    func_28F510(w, 0x1A, func_28AA30(D_00484A70, 0x64), 0);
    func_28F510(w, 0x1A, func_28AA30(D_00484A70, 0xC), 1);
    func_28F510(w, 0x1A, func_28AA30(D_00484A70, 0xD), 2);

    func_131B60(&lay, 0, 0x34);
    lay.f0 = func_28FE10(w, 0x1A, 0);
    lay.f4 = func_28F620(w, 0x1A, 0);
    lay.f8 = 0xAA;
    lay.f10 = 0x1E;
    lay.f14 = 0x30;
    lay.f18 = 0xF;
    lay.f1C = 8;
    lay.f30 = 1;
    cw = func_28F400(w, 0x1A, 0) + 0x1E;
    ch = func_28F3D0(w, 0x1A, 0) + 0x30;
    if (cw < 0xFA) {
        lay.f10 = 0x118 - cw;
        cw = 0xFA;
    }
    y = func_1451D0(func_15DE80()) / 2 - ch / 2;
    r = cw + 0x9A;

    g = func_28EA40(D_00484A44->f68, 0x88C2);
    g->f4 = 0xC5;
    g->f6 = y + 0x24;
    g->f8 = r - 0x13A;
    func_290F60(D_004807EC, 0x97, g->f4, g->f6);
    func_28FD10(w, 0x1D, 0xE3, y + 0x24, 0);
    func_28FD10(w, 0x1D, 0xE7, y + 0x24, 1);
    func_28FD10(w, 0x1D, 0x117, y + 0x24, 2);
    row = func_28FE10(w, 0x1D, 0);
    row->f18 = r - 0x13A;
    row = func_28FE10(w, 0x1D, 1);
    row->f18 = r - 0x13A;
    row = func_28FE10(w, 0x1D, 2);
    row->f18 = r - 0x13A;
    func_28FD10(w, 0x1D, 0xE5, y + 0x24, 3);
    func_28D0C0(&lay, 0, 0, 0);

    func_28F550(w, 0x1A, y + 8, 0);
    func_28F300(w, 0x1A, (cw - 0x20) / 2 + 0xBA, 0);
    func_28F550(w, 0x1A, y + 0x28, 1);
    func_28F300(w, 0x1A, 0xFD, 1);
    func_28F550(w, 0x1A, y + 0x28, 2);
    func_28F300(w, 0x1A, r - 0x3D, 2);
    func_28FD70(w, 0x1C, 0xB4, y + 0x1B, 0xA, 6, 0);
    func_28FD70(w, 0x1C, 0xBE, y + 0x1B, cw - 0x2B, 6, 1);
    func_28FD70(w, 0x1C, cw + 0x93, y + 0x1B, 0xA, 6, 2);

    D_00484A84 = 0;
    func_290010(w, 0x1A, 1, -1);
    func_290010(D_004807EC, 0x97, 1, -1);
    func_291110(w, 0x1B, 0, 1);
    func_291110(w, 0x1C, 1, 1);
    func_291110(w, 0x1D, 1, 1);
    func_290690(w, 0x1A, 1.0f, 0.125f, -1.0f);
    func_290690(w, 0x1E, 0.0f, 0.125f, -1.0f);
    func_290690(D_004807EC, 0x97, 1.0f, 0.125f, -1.0f);
    D_00484A44->f78 = 1;
    factory_FactoryMenuCursorBob_4f0f30(D_00484A44, 1);
}
