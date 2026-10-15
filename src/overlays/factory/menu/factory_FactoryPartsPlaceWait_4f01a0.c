#include "types.h"

typedef struct B {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} B;

typedef struct C {
    s32 f00;
} C;

typedef struct A {
    u8    pad00[0x64];
    s32   f64;
    s32   f68;
    u8    pad6C[0x1C];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
} A;

extern C    *func_367EC0(void);
extern void *func_207DF0(void);
extern void  func_1B9520(void *p, s32 a, s32 b, f32 t);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern B    *func_28EA40(void *w, s32 id);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);

void factory_FactoryPartsPlaceWait_4f01a0(A *o)
{
    B    *r;
    C    *q;
    void *p;

    if (o->f88 == 1) {
        q = func_367EC0();
        if (q->f00 == 0) {
            p = func_207DF0();
            func_1B9520(p, 6, 0, 1.0f);
            func_28EA90(o->f90, 0x88F4, 0);
            r = func_28EA40(o->f90, 0x88F4);
            r->f16 = o->f64;
            r->f1A = o->f68;
            func_290690(o->f8C, 0x42, 1.0f, 0.125f, -1.0f);
            func_290690(o->f8C, 0x4C, 1.0f, 0.125f, -1.0f);
            func_290690(o->f8C, 0x45, 0.0f, -0.125f, -1.0f);
            func_290690(o->f8C, 0x47, 0.0f, -0.125f, -1.0f);
            o->f88 = 0;
        }
    }
}
