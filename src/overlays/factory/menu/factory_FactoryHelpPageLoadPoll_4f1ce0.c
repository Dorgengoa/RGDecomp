#include "types.h"

typedef struct Ent {
    s16 f0;
    s16 f2;
} Ent;

typedef struct Ctx {
    u8    pad00[0x68];
    s16   f68;
    u8    pad6A[0x2];
    s32   f6C;
    u8    f70;
    u8    f71;
    u8    pad72[0x2];
    Ent  *f74;
    s32   f78;
    s32   f7C;
    s32   f80;
    u8    pad84[0x4];
    void *f88;
} Ctx;

extern void *D_00484A30;                        /* _gp - 0x740  */
extern void *D_00484A70;                        /* _gp - 0x700  */
extern void *D_004807E8;                        /* _gp - 0x4988 */

extern void *func_1F59D0(void);
extern s32   func_1CD4F0(void *h, s32 id);
extern void  func_14D8E0(void *p);
extern void *func_14D9D0(void *p, s32 a);
extern void *func_1CD490(void *h, s32 id, s32 *sz);
extern void  func_14DA10(void *p, s32 n);
extern void  func_1319A8(void *d, void *s, s32 n);
extern void *func_15DE40(void);
extern void  func_1594D0(void *a, void *b, s32 c, void *d, s32 e);
extern void  func_1CD340(void *h, s32 id);
extern void *func_28AA30(void *p, s32 id);
extern s32   func_1347C0(void *p, s32 a);
extern void  func_290AC0();
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);

void factory_FactoryHelpPageLoadPoll_4f1ce0(Ctx *c)
{
    void *h;
    void *s;
    void *d;
    void *p;
    s32   sz;
    s32   r;
    s32   t;

    if (c->f80 != 0) {
        return;
    }
    if (c->f7C == -1) {
        return;
    }
    h = func_1F59D0();
    c->f80 = func_1CD4F0(h, c->f7C);
    if (c->f80 != 1) {
        return;
    }
    c->f71 = 1;
    func_14D8E0(D_00484A30);
    d = func_14D9D0(D_00484A30, 1);
    s = func_1CD490(h, c->f7C, &sz);
    func_14DA10(D_00484A30, sz / 16 + 1);
    func_1319A8(d, s, sz);
    func_1594D0(func_15DE40(), d, 0x32E, D_00484A30, 0);
    func_1CD340(h, c->f7C);
    c->f7C = -1;
    p = func_28AA30(D_00484A70, c->f78 + (c->f74[c->f6C].f0 + 0x2710));
    r = func_1347C0(p, 0xA);
    t = r + 1;
    if (c->f70 == 2) {
        func_290AC0(c->f88, 0x84, t);
        func_290010(c->f88, 0x84, 1, -1);
        func_290690(c->f88, 0x84, 1.0f, 0.125f, -1.0f);
        c->f68 = 0;
        func_290010(D_004807E8, 0x96, 1, -1);
        func_290690(D_004807E8, 0x96, 1.0f, 0.125f, 0.0f);
        c->f70 = 1;
    } else if (c->f70 == 3) {
        if (c->f78 % 2 == 0) {
            func_290AC0(c->f88, 0x84);
            func_290010(c->f88, 0x84, 1, -1);
            func_290690(c->f88, 0x84, 1.0f, 0.125f, -1.0f);
        } else {
            func_290AC0(c->f88, 0x85);
            func_290010(c->f88, 0x85, 1, -1);
            func_290690(c->f88, 0x85, 1.0f, 0.125f, -1.0f);
        }
        c->f70 = 1;
    }
}
