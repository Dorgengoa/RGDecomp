#include "types.h"

/* title.bin overlay, 0x004ECE80 -- BYTE-IDENTICAL (session 12).
 *
 * Build the title screen's widget set.  0.7f appears four times and is CSE'd
 * to one pool load; 0.4f once.
 *
 * ⚠ HISTORY, because this unit was parked for five sessions on a WRONG cause.
 * It read `extern f32 D_0047D248 / 0047D56C (0.7f and 0.4f)` and sat at 2 bad word(s), recorded as a
 * scheduler-internal tie-break "negative on five axes".  0x0047D1D0-0x0047D7FF
 * is not a table of globals: it is mwcc's `.lit4` FLOAT LITERAL POOL (pi,
 * pi/20, pi/40, 1/6, 0.05, -0.1, 0.4, 1e-4, with 0.4 stored twice), and retail
 * wrote the LITERAL.  Both spellings emit the same `lwc1 $fN, K($28)`; only a
 * pool entry may be hoisted past the prologue's stack stores, which is exactly
 * retail's schedule.  Every one of those five sweeps held the `extern`
 * spelling fixed.  See memory levers.d/mwcc-float-literal-pool.md.
 *
 * The `.lit4` section this now emits is resolved to the retail pool address by
 * scripts/t_lit4.py, which t_olink.py calls for every object it links.
 */

typedef struct Widget {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad8[4];
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    s16 f20;
} Widget;

typedef struct Slot {
    u8 pad0[0x20];
    Widget *f20;
} Slot;

typedef struct Title {
    u8 pad0[4];
    void *f4;
    s8 f8;
    u8 pad9[3];
    s16 fC;
    s16 fE;
    s16 f10;
    u8 pad12[2];
    f32 f14;
    f32 f18;
} Title;

extern void *D_0048415C;
extern void *D_00484174;
extern s16 D_0048419C;

extern s32 func_206A40(void);
extern void func_206AF0(s32 a);
extern s32 func_206B00(void);
extern s32 func_207F20(void);
extern Widget *func_28EA40(void *a, s32 b);
extern void func_290010(void *a, s32 b, s32 c, s32 d);
extern Slot *func_290460(void *a, s32 b);
extern void func_2907A0(void *a, s32 b, f32 v);
extern void func_290F60(void *a, s32 b, s32 x, s32 y);
extern void func_291110(void *a, s32 b, s32 c, s32 d);
extern u8 func_372FB0(void);
extern s32 func_42C3A0(s32 a, s32 b);
extern s32 title_TitleAnySaveExists_4ed380(void);

s32 title_TitleMenuWidgetsSetup_4ece80(Title *o, void *p)
{
    Slot *s;
    Slot *z;
    Widget *w;
    s32 t;
    s32 q;
    f32 v;

    if (p == 0) {
        return 1;
    }
    o->f4 = p;
    func_291110(o->f4, 1, 1, 1);
    s = func_290460(o->f4, 2);
    func_291110(o->f4, 2, 1, 1);
    t = func_206A40();
    D_0048419C = func_372FB0();
    if (func_207F20() != 0) {
        s->f20 = (Widget *)func_42C3A0(t, 0x756C);
        func_291110(o->f4, 3, 0, 1);
        func_291110(o->f4, 4, 0, 1);
        func_291110(o->f4, 5, 0, 1);
        func_291110(o->f4, 0x66, 0, 1);
        z = func_290460(o->f4, 6);
        z->f20->f20 = 0xD0;
    } else {
        s->f20 = (Widget *)func_42C3A0(t, 0x7562);
        func_291110(o->f4, 3, 1, 1);
        func_291110(o->f4, 4, 1, 1);
        func_291110(o->f4, 5, 1, 1);
        if (D_0048419C != 0) {
            func_291110(o->f4, 0x66, 1, 1);
        } else {
            func_291110(o->f4, 0x66, 0, 1);
        }
        z = func_290460(o->f4, 6);
        z->f20->f20 = -1;
    }
    func_290F60(o->f4, 1, 0, 0);
    func_291110(D_00484174, 0x46, 0, 1);
    if (title_TitleAnySaveExists_4ed380() != 0) {
        func_206AF0(1);
    } else {
        func_206AF0(0);
    }
    q = 0;
    if (func_207F20() == 0) {
        q = (s8)func_206B00();
        if (q < 0) {
            q = 0;
        }
    }
    func_290F60(o->f4, 2, 0xB4, q * (0x18 - D_0048419C * 4) + 0x136);
    if (q != 0) {
        func_2907A0(o->f4, 3, 0.7f);
        func_2907A0(o->f4, 4, 1.0f);
    } else {
        func_2907A0(o->f4, 3, 1.0f);
        func_2907A0(o->f4, 4, 0.7f);
    }
    func_2907A0(o->f4, 5, 0.7f);
    func_2907A0(o->f4, 0x66, 0.7f);
    o->fC = 1;
    o->f10 = 0;
    v = 0.4f;
    o->fE = o->fC;
    o->f14 = 1.0f;
    o->f18 = v;
    o->f8 = 0;
    func_290F60(o->f4, 3, 0xB8, 0x13B);
    if (D_0048419C != 0) {
        func_290F60(o->f4, 4, 0xB8, 0x14F);
        func_290F60(o->f4, 0x66, 0xB9, 0x163);
        func_290F60(o->f4, 5, 0xB9, 0x177);
        w = func_28EA40(D_0048415C, 0x7531);
        w->fE = 3;
    } else {
        func_290F60(o->f4, 4, 0xB8, 0x153);
        func_290F60(o->f4, 5, 0xB9, 0x16B);
        w = func_28EA40(D_0048415C, 0x7531);
        w->fE = 2;
    }
    func_290F60(o->f4, 6, 0x89, 0x18A);
    w = func_290460(o->f4, 3)->f20;
    w->f6 = 0x10;
    w->f4 = 0x8E;
    w->fE = 0x10;
    w->fC = 0x8E;
    w = func_290460(o->f4, 4)->f20;
    w->f6 = 0x10;
    w->f4 = 0x8E;
    w->fE = 0x10;
    w->fC = 0x8E;
    func_2907A0(o->f4, 1, 0.0f);
    func_290F60(o->f4, 1, 0, 0);
    func_290010(o->f4, 7, 0, -1);
    func_290010(o->f4, 8, 0, -1);
    func_290010(o->f4, 0xA, 0, -1);
    func_290010(o->f4, 0x47, 0, -1);
    func_290010(o->f4, 0x48, 0, -1);
    return 0;
}
