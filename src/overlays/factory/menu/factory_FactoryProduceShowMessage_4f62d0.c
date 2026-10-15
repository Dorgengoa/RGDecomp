#include "types.h"

/* factory.bin overlay, 0x004F62D0 -- lay out the factory screen's message box
 * for one prompt kind.
 *
 * 520 instructions, TWO jump tables (jtbl_0050CC80 for `kind` 0..5 and
 * jtbl_0050CC40 for the sub-kind 8..21).  Both are the overlay's own data, and
 * scripts/f_jtbl.py is what lets a compiled `switch` use them instead of
 * emitting a second copy into the object's .rodata.
 *
 * ★ The four-store + func_28D0C0 tail is an INLINED HELPER, not a shared
 * label: retail emits it five times -- once at the end of each of cases 1, 2,
 * 3 and 5, and once after case 4's inner switch, which every inner arm
 * `break`s out to.  A shared `goto` would have emitted it once.
 *
 * ★ Case 0 is the only arm that computes its own four values, so it does not
 * use the helper; it calls func_28D0C0 itself.
 *
 * ★ `sra` with a +1 bias under `bgez` is a signed `/ 2`; m2c writes the bias
 * out longhand and the plain division compiles to the same code.
 *
 * ★ D_0050CC38 and D_0050FED0 are OVERLAY data at 0x50xxxx, far outside the
 * gp window 0x47D170..0x48D170, so they must not take a %gp_rel relocation.
 * An INCOMPLETE array type is what gives them `lui %hi` + `addiu %lo`.
 *
 * ⚠ The default of the inner switch calls this function RECURSIVELY with
 * kind 3 and then sets the sub-kind to 6; it does not fall into the tail.
 */

typedef struct Style {
    u8  pad0[0xC];
    s32 fC;
    u8  pad10[0x9C];
} Style;

typedef struct Layout {
    s32 f0;
    s32 f4;
    u8  pad8[8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Layout;

typedef struct Panel {
    u8   pad0[0x70];
    s16  f70;
    u8   f72;
    u8   pad73;
    s16 *f74;
    u8   pad78[0xC];
    void *f84;
} Panel;

extern void *D_00484A70;
extern u8 D_0050CC38[];
extern u8 D_0050FED0[];

extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_207340(s32 id, s32 a, f32 g);
extern void  func_28A9A0(void *dst, void *src, void *sty, s32 f);
extern void  func_28AA00(void *sty);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern s32   func_28F3D0(void *ctx, s32 id, s32 a);
extern s32   func_28F400(void *ctx, s32 id, s32 a);
extern void  func_28F510(void *ctx, s32 id, void *p, s32 a);
extern void  func_28F5D0(void *ctx, s32 id, s32 x, s32 y, s32 f);
extern s32   func_28F620(void *ctx, s32 id, s32 a);
extern void  func_28FD10(void *ctx, s32 id, s32 x, s32 y, s32 f);
extern void  func_28FD70(void *ctx, s32 id, s32 x, s32 y, s32 w, s32 h, s32 n);
extern s32   func_28FE10(void *ctx, s32 id, s32 a);

extern void factory_FactoryProduceShowMessage_4f62d0(Panel *o, s16 kind);

static inline void endBox(Layout *lay)
{
    lay->f10 = 0x1E;
    lay->f14 = 0x13;
    lay->f18 = 0xF;
    lay->f1C = 0xB;
    func_28D0C0(lay, 0, 0, 0);
}

void factory_FactoryProduceShowMessage_4f62d0(Panel *o, s16 kind)
{
    Layout lay;
    Style sty;
    s32 w;
    s32 h;
    s32 cx;
    s32 cy;
    s32 x;
    s32 y;
    s32 ty;

    func_131B60(&lay, 0, 0x34);
    lay.f0 = func_28FE10(o->f84, 0x8B, 0);
    lay.f4 = func_28F620(o->f84, 0x8B, 0);
    func_28AA00(&sty);
    func_131B60(&sty, 0, 0xAC);
    func_28F510(o->f84, 0x8B, D_0050CC38, 0);
    func_28F510(o->f84, 0x8E, D_0050CC38, 0);

    switch (kind) {
    case 0:
        sty.fC = *o->f74;
        func_131B60(D_0050FED0, 0, 0x40);
        func_28A9A0(D_0050FED0, func_28AA30(D_00484A70, 0x22), &sty, 1);
        func_28F510(o->f84, 0x8B, D_0050FED0, 0);
        func_28F510(o->f84, 0x8E, func_28AA30(D_00484A70, 0x1E), 0);
        w = func_28F400(o->f84, 0x8B, 0) + 0x3C;
        h = func_28F400(o->f84, 0x8E, 0);
        if (w < h) {
            lay.f10 = (h - w) + 0x5A;
        } else {
            lay.f10 = 0x5A;
        }
        lay.f14 = 0x35;
        lay.f18 = 0x4E;
        lay.f1C = 0xE;
        cx = lay.f10 + func_28F400(o->f84, 0x8B, 0);
        cy = lay.f14 + func_28F3D0(o->f84, 0x8B, 0);
        x = 0x100 - cx / 2;
        y = 0xE0 - cy / 2;
        func_28FD10(o->f84, 0x8E, x + 0x17, y + 8, 0);
        func_28FD10(o->f84, 0x8F, x + 0x1D, y + 0xF, 0);
        func_28FD10(o->f84, 0x90, x + 0x1D, y + 0xF, 0);
        func_28F5D0(o->f84, 0x8E, x + 0x12, y + 0x46, 0);
        ty = y + (cy - lay.f14) + 0xF;
        func_28FD70(o->f84, 0x8D, x + 0xA, ty, 0xA, 6, 0);
        func_28FD70(o->f84, 0x8D, x + 0x14, ty, cx - 0x2A, 6, 1);
        func_28FD70(o->f84, 0x8D, x + 8 + (cx - 0x1E), ty, 0xA, 6, 2);
        func_28D0C0(&lay, 0, 0, 0);
        break;

    case 1:
        sty.fC = *o->f74;
        func_131B60(D_0050FED0, 0, 0x40);
        func_28A9A0(D_0050FED0, func_28AA30(D_00484A70, 0xB4), &sty, 1);
        func_28F510(o->f84, 0x8B, D_0050FED0, 0);
        func_207340(0x321, 0, 1.0f);
        endBox(&lay);
        break;

    case 2:
        sty.fC = *o->f74;
        func_131B60(D_0050FED0, 0, 0x40);
        func_28A9A0(D_0050FED0, func_28AA30(D_00484A70, 0x20), &sty, 1);
        func_28F510(o->f84, 0x8B, D_0050FED0, 0);
        func_207340(0x321, 0, 1.0f);
        endBox(&lay);
        break;

    case 3:
        sty.fC = *o->f74;
        func_131B60(D_0050FED0, 0, 0x40);
        func_28A9A0(D_0050FED0, func_28AA30(D_00484A70, 0x21), &sty, 1);
        func_28F510(o->f84, 0x8B, D_0050FED0, 0);
        endBox(&lay);
        break;

    case 4:
        switch (o->f70) {
        case 8:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7532), 0);
            break;
        case 9:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7530), 0);
            break;
        case 10:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7533), 0);
            break;
        case 11:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7531), 0);
            break;
        case 12:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x753B), 0);
            break;
        case 13:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x753C), 0);
            break;
        case 14:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x753A), 0);
            break;
        case 15:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7534), 0);
            break;
        case 16:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7535), 0);
            break;
        case 17:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7536), 0);
            break;
        case 19:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7537), 0);
            break;
        case 20:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7538), 0);
            break;
        case 21:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x7539), 0);
            break;
        case 18:
            func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x753D), 0);
            break;
        default:
            factory_FactoryProduceShowMessage_4f62d0(o, 3);
            o->f72 = 6;
            return;
        }
        endBox(&lay);
        break;

    case 5:
        func_28F510(o->f84, 0x8B, func_28AA30(D_00484A70, 0x1F), 0);
        endBox(&lay);
        break;
    }
}
