#include "types.h"

typedef struct V3 { f32 x, y, z; } V3;
typedef struct V4 { f32 x, y, z, w; } V4;

extern "C" void BoundsAddPoint_13dee0(V4 *, V4 *, V4 *);

class C {
public:
    s32 m0;
    s32 m4;
    u8 pad8[8];
    V4 a;
    V4 b;
    virtual s32 v0(s32, s32, s32, s32);
    virtual s32 v1(s32, s32, s32, s32);
    virtual s32 v2(s32, s32, s32, s32);
    virtual s32 v3(s32, s32, s32, s32);
    virtual s32 v4(s32, s32, s32, s32);
    virtual s32 v5(s32, s32, s32, s32);
    virtual s32 v6(s32, s32, s32, s32);
    virtual s32 v7(s32, s32, s32, s32);
    virtual s32 v8(s32, s32, s32, s32);
    virtual s32 v9(s32, s32, s32, s32);
    virtual s32 v10(s32, s32, s32, s32);
    u8 pad34[0xC];
    s32 n;
    V3 *pts;
};

extern "C" s32 CollMeshCollectTrisAll_16d2c0(C *o, s32 a, s32 b, s32 c)
{
    return o->v10(3, a, b, c);
}

extern "C" void func_0016D2F0(C *o)
{
    V3 *p = o->pts;
    V3 *q;
    s32 i;
    V4 t;
    if (p == 0 || o->n <= 0) return;
    o->a.x = p->x; o->a.y = p->y; o->a.z = p->z; o->a.w = 1.0f;
    q = o->pts;
    o->b.x = q->x; o->b.y = q->y; o->b.z = q->z; o->b.w = 1.0f;
    for (i = 1; i < o->n; i++) {
        t.x = o->pts[i].x; t.y = o->pts[i].y; t.z = o->pts[i].z; t.w = 1.0f;
        BoundsAddPoint_13dee0(&o->a, &o->b, &t);
    }
    o->m4 = 1;
}
