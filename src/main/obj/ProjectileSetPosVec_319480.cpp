#include "types.h"

/* ProjectileSetPosVec_319480 -- 52 B, TWO entries.  vptr at 0xB0 (non-polymorphic base). */

struct V319B { unsigned char pad[0xB0]; };
class V319 : public V319B {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19(f32, f32, f32);
};

struct S319 { u8 pad000[0x1B0]; f32 m1B0; f32 m1B4; f32 m1B8; s32 m1BC; };

struct Vec319 { f32 x; f32 y; f32 z; };

extern "C" void ProjectileSetPosVec_319480(V319 *o, Vec319 *v) { o->v19(v->x, v->y, v->z); }

extern "C" void func_00319480_e1(S319 *o, f32 a, f32 b, f32 c)
{
    o->m1B0 = a;
    o->m1B4 = b;
    o->m1B8 = c;
    o->m1BC = 0;
}
