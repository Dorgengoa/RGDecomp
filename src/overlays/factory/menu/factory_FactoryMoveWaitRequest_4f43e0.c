#include "types.h"

typedef struct Glob {
    u8    pad00[0x5C];
    u8    f5C;
    u8    pad5D[0x3];
    void *f60;
} Glob;

typedef struct St {
    s32 f00;
    s32 f04;
} St;

typedef struct Buf {
    s32 f00;
    s32 f04;
    u8  pad08[0x8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Buf;                                          /* 0x34 */

extern u8    D_004B2570[0x10];
extern void *D_00484A70;                        /* _gp - 0x700 */

extern St  *func_367EC0(void);
extern s32  func_1839F0(u8 *p, s32 mask);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern void func_2907A0(void *h, s32 id, f32 a);
extern void *func_28AA30(void *h, s32 id);
extern void func_28F510(void *h, s32 id, void *p, s32 a);
extern void func_131B60(void *p, s32 v, s32 n);
extern s32  func_28FE10(void *h, s32 id, s32 a);
extern s32  func_28F620(void *h, s32 id, s32 a);
extern void func_28D0C0(Buf *b, s32 a, s32 c, s32 d);
extern void *func_207DF0(void);
extern void func_1B9520(void *m, s32 id, s32 a, f32 v);

s32 factory_FactoryMoveWaitRequest_4f43e0(Glob *g)
{
    Buf b;
    St *s;

    s = func_367EC0();
    if (g->f5C == 1) {
        if (func_1839F0(D_004B2570, 0x40) != 0 || func_1839F0(D_004B2570, 0x20) != 0) {
            func_290690(g->f60, 0x51, 0.0f, -0.125f, -1.0f);
            s->f00 = 6;
            g->f5C = 0;
            return 0;
        }
    }
    if (s->f04 == 3) {
        func_2907A0(g->f60, 0x51, 0.0f);
        func_28F510(g->f60, 0x51, func_28AA30(D_00484A70, 0xA0), 0);
        func_131B60(&b, 0, 0x34);
        b.f00 = func_28FE10(g->f60, 0x51, 0);
        b.f04 = func_28F620(g->f60, 0x51, 0);
        b.f10 = 0x1E;
        b.f14 = 0x13;
        b.f18 = 0xF;
        b.f1C = 0xB;
        func_28D0C0(&b, 0, 0, 0);
        func_290690(g->f60, 0x51, 1.0f, 0.125f, -1.0f);
        s->f00 = 1;
        s->f04 = -1;
        g->f5C = 1;
        return 0;
    }
    if (s->f00 == 0) {
        func_1B9520(func_207DF0(), 6, 0, 1.0f);
        return 1;
    }
    return 0;
}
