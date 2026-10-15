#include "types.h"

typedef struct B {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
} B;

typedef struct A {
    u8    pad00[0x5C];
    s16   f5C;
    s16   f5E;
    s16   f60;
    s16   f62;
    f32   f64;
    u8    pad68[0x4];
    u8    f6C;
    u8    pad6D[0x3];
    s32   f70;
    s32   f74;
    s16   f78;
    s16   f7A;
    u8    f7C;
    u8    pad7D[0x3];
    void *f80;
    void *f84;
    u8    pad88[0xC];
    s32   f94;
    u8    f98[0x20];
} A;

extern f32   D_0047D4F4;
extern void *D_004807E8;
extern void *D_004807EC;
extern void *D_00484A70;

extern void  func_28DB70(void *g);
extern void  func_28DA30(void *g, void *w, s32 id);
extern void  func_28DB40(void *g, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 h);
extern void  func_28D9D0(void *g);
extern void  func_28D9C0(void *g, s32 a);
extern void  func_28DAA0(void *g, s32 a, s32 b, s32 c);
extern void  func_28D820(void *g, s32 a);
extern B    *func_28EA40(void *w, s32 id);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);
extern void  func_291110(void *w, s32 id, s32 a, s32 b);
extern void  func_2907A0(void *w, s32 id, f32 t);
extern void  factory_FactoryBlueprintMarkCell_4f7a40(A *o, s32 a, s32 b);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  factory_FactoryBlueprintGridBuild_4f9f50(A *o);
extern void *func_28AA30(void *p, s32 k);
extern void  func_28F510(void *w, s32 id, void *r, s32 n);
extern void  func_290BD0(void *w, s32 id, s32 a, s32 b, s32 c, s32 f);

void factory_FactoryBlueprintListInit_4fbab0(A *o)
{
    f32 v;
    B *b;

    v = D_0047D4F4;
    o->f94 = 0;
    o->f64 = -3.1415927f;
    func_28DB70(&o->f98);
    func_28DA30(&o->f98, o->f80, 0x26);
    func_28DB40(&o->f98, 0x26, 0x1A, 0x1A, 0x32, 0x38, 0, 0);
    func_28D9D0(&o->f98);
    func_28D9C0(&o->f98, 1);
    func_28DAA0(&o->f98, 0x26, 0x1A, 0x1A);
    func_28D820(&o->f98, 0x26);
    b = func_28EA40(o->f84, 0x88CC);
    func_290F60(o->f80, 0x40, b->f04, b->f06);
    func_291110(D_004807EC, 0x97, 0, 1);
    func_2907A0(D_004807EC, 0x97, 1.0f);
    factory_FactoryBlueprintMarkCell_4f7a40(o, 0, 0);
    func_291110(o->f80, 0x23, 0, 1);
    func_290010(o->f80, 0x27, 0, -1);
    func_290010(o->f80, 0x2B, 0, -1);
    if (o->f70 != 0) {
        func_290F60(o->f80, 0x29, 0, 0);
        func_290010(o->f80, 0x29, 1, -1);
    } else {
        func_290F60(o->f80, 0x29, 0xEB, 0);
        func_290010(o->f80, 0x29, 0, -1);
    }
    func_290010(D_004807E8, 0x92, 0, -1);
    func_2907A0(o->f80, 0x27, 1.0f);
    o->f7C = 0;
    o->f5C = 0;
    o->f5E = 0;
    o->f60 = 0;
    o->f62 = 0;
    o->f74 = 0;
    o->f78 = 0;
    o->f7A = 0;
    o->f6C = 0;
    factory_FactoryBlueprintGridBuild_4f9f50(o);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 0), 0);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 1), 1);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 2), 2);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 3), 3);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 4), 5);
    func_28F510(o->f80, 0x3A, func_28AA30(D_00484A70, 3), 0);
    func_28F510(o->f80, 0x3A, func_28AA30(D_00484A70, 0x1D), 3);
    func_290BD0(o->f80, 0x29, 0x200, 1, 0, 0);
    func_290BD0(o->f80, 0x29, 0x200, 1, 1, 0);
    func_28F510(o->f80, 0x29, func_28AA30(D_00484A70, 0x32), 0);
}
