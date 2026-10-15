#include "types.h"

typedef struct A {
    u8    pad00[0x5C];
    f32   f5C;
    u8    pad60[0x4];
    void *f64;
    u8    pad68[0xC];
    s32   f74;
    u8    f78;
} A;

extern f32 D_0047D4F4;

extern void func_28F670(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F970(void *w, s32 id, s32 a, s32 b, s32 c);
extern void func_28FD10(void *w, s32 id, s32 a, s32 b, s32 c);
extern void func_290F60(void *w, s32 id, s32 x, s32 y);
extern void func_290010(void *w, s32 id, s32 a, s32 b);

void factory_FactoryMenuReset_4f10f0(A *o)
{
    f32 v;

    v = D_0047D4F4;
    o->f74 = 0;
    o->f5C = -3.1415927f;
    func_28F670(o->f64, 0x18, 0, 0, 0, 0, 0);
    func_28F970(o->f64, 0x19, 0x40, 0xC0, 0);
    func_28FD10(o->f64, 0x19, 0xB, 0x31, 0);
    func_28F670(o->f64, 4, 0, 0, 0, 0, 3);
    func_28F670(o->f64, 4, 0x73, 0x1E, 0x4C, 0x18, 4);
    func_290F60(o->f64, 4, 0xF, 0);
    func_290010(o->f64, 0xC, 0, -1);
    func_290010(o->f64, 0x1A, 0, -1);
    o->f78 = 0;
}
