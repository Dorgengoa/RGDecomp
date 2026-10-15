#include "types.h"

/* factory.bin overlay, 0x004FD2F0 -- the smoke/spark emitter phase of a running
 * machine: spawn a particle at a random attachment once every sixty frames,
 * flicker the light parts, and pulse the node scale off a sine.  708 bytes.
 */

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Part {
    u8   pad00[0x3C];
    s32  f3C;
} Part;

typedef struct Ent {
    s32 f00;
    s32 f04;
    s32 f08;
} Ent;

typedef struct Kind {
    u8    pad00[0x50];
    s32  *f50;
    Ent  *f54;
} Kind;

typedef struct Src {
    u8    pad00[0x20];
    u8    f20;
    u8    pad21[0x3];
    Kind *f24;
} Src;

typedef struct Slot {
    u8    pad00[0x20];
    Node *f20;
    s8    f24;
    s8    f25;
    u8    pad26[0x1];
    s8    f27;
    s16   f28;
} Slot;

typedef struct Emit {
    u8  pad00[0x8];
    s32 f08;
    u8  pad0C[0x14];
} Emit;

extern void factory_FactoryPartObjSetNodesVisible_4fd110(Slot *o, Kind *k, u8 a);
extern void factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(Slot *o, Kind *k, s32 on);
extern void factory_FactoryPartObjSetFuncFlag_4fd260(Slot *o, Kind *k, s32 on);
extern void factory_FactoryPartObjSetNodes2Visible_4fd1b0(Slot *o, Kind *k, s32 on);
extern s32  func_1F5BE0(void);
extern s32  func_2D9040(void);
extern s32  func_133710(void);
extern Part *func_195040(Node *nd, s32 h);
extern void func_186650(Part *p, f32 *v);
extern void func_194350(Node *nd, f32 *m);
extern void func_1CB8E0(f32 *d, f32 *m, f32 *v);
extern void func_2E1020(Emit *e, s32 r, s32 id, s32 a);
extern void func_2E0100(s32 r, Emit *e, s32 a);
extern void func_2E0BB0(s32 r, Emit *e, f32 *v);
extern void func_2E01C0(s32 r, Emit *e, s32 a);
extern f32  func_1CBF30(f32 x);
extern f32  func_128FD0(f32 x);
extern void func_1865B0(Node *nd, f32 *v);
extern f32  D_0047D404;

void factory_FactoryPartObjStateWork_4fd2f0(Slot *o, Src *s)
{
    f32   mtx[16];
    f32   vec[4];
    Emit  e;
    f32   sc[4];
    Node *nd;
    Part *x;
    Ent  *ep;
    s32  *pp;
    s32   r;
    s32   h;
    f32   k;
    s8   *p;
    u32   m;

    o->f20->f32 = 1;
    factory_FactoryPartObjSetNodesVisible_4fd110(o, s->f24, s->f20);
    if (o->f24 != o->f25) {
        factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, s->f24, 1);
        factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 1);
        factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, s->f24, 1);
        o->f24 = o->f25;
        o->f28 = 0;
    }
    switch (o->f27) {
    case 0:
        func_1F5BE0();
        o->f27 = o->f27 + 1;
        o->f28 = 0;
        break;
    case 1:
        ep = s->f24->f54;
        if (ep != NULL) {
            r = func_2D9040();
            while (ep->f00 != 0) {
                if (func_133710() % 0x3C == 0) {
                    x = func_195040(o->f20, ep->f00);
                    if (x != NULL) {
                        func_186650(x, vec);
                        func_194350(o->f20, mtx);
                        func_1CB8E0(vec, mtx, vec);
                        func_2E1020(&e, r, ep->f04, -1);
                        if (e.f08 >= 0) {
                            func_2E0100(r, &e, -1);
                            func_2E0BB0(r, &e, vec);
                            func_2E01C0(r, &e, ep->f08);
                        }
                    }
                }
                ep++;
            }
        }
        pp = s->f24->f50;
        if (pp != NULL) {
            while ((h = *pp) != 0) {
                x = func_195040(o->f20, h);
                if (x != NULL) {
                    if ((func_133710() & 1) != 0) {
                        x->f3C = x->f3C & ~1;
                    } else {
                        x->f3C = x->f3C | 1;
                    }
                }
                pp++;
            }
        }
        break;
    }
    k = func_128FD0(func_1CBF30(D_0047D404 * (f32)o->f28)) / 64.0f;
    nd = o->f20;
    p = (s8 *)sc;
    m = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            m--;
            p++;
        } while (m != 0);
    }
    sc[0] = 1.0f - k;
    sc[1] = 1.0f + 2.0f * k;
    sc[2] = 1.0f - k;
    func_1865B0(nd, sc);
    o->f28 = o->f28 + 1;
}
