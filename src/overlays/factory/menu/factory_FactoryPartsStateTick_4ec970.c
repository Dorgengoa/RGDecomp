#include "types.h"

typedef struct Ctx {
    u8    pad00[0x20];
    void *f20;
    u8    pad24[0x64];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
    void *f94;
    u8    pad98[0x4];
    u8    f9C;
} Ctx;

typedef struct Grid {
    u8    pad00[0x70];
    void *f70;
    u8    pad74[0x1C];
    u8    f90;
} Grid;

typedef struct Msg {
    s32 f0;
} Msg;

extern Ctx  *D_00484A4C;                        /* _gp - 0x724 */
extern Grid *D_00484A48;                        /* _gp - 0x728 */
extern const u8 D_004B2570[];

extern void  func_28EA90(void *w, s32 id, s32 a);
extern Ctx  *func_290460(void *w, s32 id);
extern void  func_28D580(void *p, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28DB70(void *p);
extern void  func_28DA30(void *p, void *q, s32 a);
extern void  func_28DB40(void *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void  func_28D9D0(void *p);
extern void  func_28D9C0(void *p, s32 a);
extern void  func_28DAA0(void *p, s32 a, s32 b, s32 c);
extern void  func_28D820(void *p, s32 a);
extern s32   func_28E170(void *w, const u8 *p, s32 a, s32 b);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s32   func_1839F0(const u8 *p, s32 mask);
extern void *func_207DF0(void);
extern void  func_1B9520(void *p, s32 a, s32 b, f32 t);
extern Msg  *func_367EC0(void);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void  factory_FactoryPartsNoStockCloseMaybe_4f0100(Ctx *c);
extern void  factory_FactoryPartsSelect_4f02c0(Ctx *c);
extern void  factory_FactoryPartsPlaceWait_4f01a0(Ctx *c);

s32 factory_FactoryPartsStateTick_4ec970(s32 unused, s32 start)
{
    void *v;
    void *w;
    void *g;
    Ctx  *p;
    Ctx  *c;
    Msg  *m;
    u8    flag;
    s32   r;

    v = D_00484A4C->f8C;
    w = D_00484A4C->f94;
    if (start != 0) {
        func_28EA90(D_00484A4C->f90, 0x88F4, 0);
        p = func_290460(v, 0x42);
        if (p != 0) {
            if (p->f20 != 0) {
                func_28D580(p->f20, 0, 0, 0x95, 0x170, 0);
            }
        }
        g = &D_00484A4C->f9C;
        func_28DB70(g);
        func_28DA30(g, v, 0x4B);
        func_28DB40(g, 0x4B, 0x1A, 0x1A, 0x4C, 0x4C, 0, 0);
        func_28D9D0(g);
        func_28D9C0(g, 1);
        func_28DAA0(g, 0x4B, 0x1A, 0x1A);
        func_28D820(g, 0x4B);
    }
    c = D_00484A4C;
    flag = 0;
    if (c->f88 == 1) {
        flag = 1;
    }
    r = func_28E170(c->f90, D_004B2570, flag, 0);
    if (r == 2 && D_00484A4C->f88 == 0) {
        func_28EDE0(w, 0x891C, 0);
    } else if (r == 2 && D_00484A4C->f88 == 2) {
        factory_FactoryPartsNoStockCloseMaybe_4f0100(D_00484A4C);
    } else if (r == 1) {
        factory_FactoryPartsSelect_4f02c0(D_00484A4C);
    } else if (func_1839F0(D_004B2570, 0x80) != 0 && D_00484A4C->f88 == 1) {
        func_1B9520(func_207DF0(), 5, 0, 1.0f);
        m = func_367EC0();
        m->f0 = 1;
        D_00484A48->f90 = 1;
        if (D_00484A48->f70 != 0) {
            func_28EDE0(w, 0x88F4, 0);
        } else {
            func_28EDE0(w, 0x88D6, 0);
        }
        func_290690(v, 0x41, 0.0f, -0.125f, -1.0f);
    } else {
        factory_FactoryPartsPlaceWait_4f01a0(D_00484A4C);
    }
    return 1;
}
