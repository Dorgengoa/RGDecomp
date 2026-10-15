#include "types.h"
/* normal 0x004EA1A0 -- builds one window: pull the 4 floats out of the
 * func_290460 record, look the caption up with func_159FB0, then walk the
 * whole func_13Exxx setter list off the func_141B00 handle, scaling the four
 * floats by 128.0f for func_13EE40. */

typedef struct Ea1Rec {
    u8   pad000[4];
    u8   f004[0x20 - 0x4];
    struct Ea1Ent *f020;
    u8   pad024[0x30 - 0x24];
    f32  f030[4];
} Ea1Rec;

typedef struct Ea1Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s16 f008;
    s16 f00A;
    u8  pad00C[0x1C - 0xC];
    u16 f01C;
} Ea1Ent;

typedef struct Ea1Cap {
    s16 f000;
} Ea1Cap;

typedef struct Ea1Obj {
    u8 pad000[0x14];
    u8 f014[0x100 - 0x14];
} Ea1Obj;

extern void    *func_15DE80(Ea1Obj *p);
extern void    *func_15DE40(void);
extern Ea1Rec  *func_290460(void *w, u16 id);
extern Ea1Cap  *func_159FB0(void *h, const void *key, s32 n);
extern void     func_1418C0(void *h, s16 v, f32 f);
extern void    *func_141B00(void *h);
extern void     func_141A20(void *h);
extern void     func_13E2F0(void *w, s32 a);
extern void     func_13E390(void *w, s32 a);
extern void     func_13E3B0(void *w, s32 a);
extern void     func_13E3D0(void *w, s32 a);
extern void     func_13E3E0(void *w, s32 a);
extern void     func_13E400(void *w, s32 a);
extern void     func_13E430(void *w, s32 a);
extern void     func_13E460(void *w, s32 a);
extern void     func_13E4D0(void *w, s32 a);
extern void     func_13E4F0(void *w, s32 a);
extern void     func_13E500(void *w, s32 a);
extern void     func_13EC00(void *w, void *s);
extern void     func_13ED60(void *w, s32 x, s32 y);
extern void     func_13EE40(void *w, s32 a, s32 b, s32 c, s32 d);
extern void     func_13F110(void *w, s32 x, s32 y, s32 z);
extern void     func_13F5B0(void *w);
extern void     func_13F730(void *w, s32 a);

void normal_MenuBattleEndDrawWindowMaybe_4ea1a0(Ea1Obj *p)
{
    f32 fv[4];
    s32 iv[4];
    void *a;
    void *b;
    Ea1Rec *r;
    Ea1Ent *e;
    Ea1Cap *c;
    void *w;
    s32 i;

    a = func_15DE80(p);
    b = func_15DE40();
    r = func_290460(p->f014, 1);
    e = r->f020;
    for (i = 0; i < 4; i++) {
        fv[i] = r->f030[i];
    }
    c = func_159FB0(b, r->f004, 0x32D);
    if (c != NULL) {
        func_1418C0(a, c->f000, 1.0f);
    }
    w = func_141B00(a);
    func_13E4F0(w, 1);
    if ((e->f01C & 1) != 0) {
        func_13E4F0(w, 2);
    }
    func_13E500(w, 1);
    func_13E390(w, 0);
    func_13E4D0(w, 1);
    func_13E460(w, 0);
    func_13E400(w, 1);
    func_13E3E0(w, 1);
    func_13E2F0(w, 0);
    if ((e->f01C & 2) != 0) {
        func_13E3D0(w, 1);
    } else {
        func_13E3D0(w, 0);
    }
    func_13E430(w, 0);
    func_13E3B0(w, 0);
    func_13F730(w, 6);
    func_13EC00(w, c);
    for (i = 0; i < 4; i++) {
        iv[i] = (s32)(128.0f * fv[i]);
    }
    func_13EE40(w, iv[0], iv[1], iv[2], iv[3]);
    func_13ED60(w, e->f008, e->f00A);
    func_13F110(w, e->f000, e->f002, 0);
    func_13ED60(w, e->f008 + 1, e->f00A + 1);
    func_13F110(w, e->f000 + e->f004, e->f002 + e->f006, 0);
    func_13F5B0(w);
    func_141A20(a);
}
