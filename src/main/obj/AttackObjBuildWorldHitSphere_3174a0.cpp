#include "types.h"

struct R_003174a0 {
    s32 f0;
    void *f4;
    s32 f8, fC, f10, f14;
    void *f18;
};

struct C_003174a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual R_003174a0 *v3(s32);
};

struct T_003174a0 {
    u8 pad[0x7C];
    s32 f7C;
    u8 pad2[0x180 - 0x80];
    f32 f180;
    u8 pad3[0xC];
    f32 f190;
};

extern "C" void HitShapeSetWorldSphere_317150(void *, f32 *, f32);

extern "C" R_003174a0 *AttackObjBuildWorldHitSphere_3174a0(T_003174a0 *p, C_003174a0 *c)
{
    R_003174a0 *r;
    void *a;

    r = c->v3(1);
    if (r == 0) return 0;
    if (r->f14 <= 0) {
        a = 0;
    } else {
        a = r->f18;
    }
    HitShapeSetWorldSphere_317150(a, &p->f180, p->f190);
    r->f4 = (void *)p->f7C;
    return r;
}
