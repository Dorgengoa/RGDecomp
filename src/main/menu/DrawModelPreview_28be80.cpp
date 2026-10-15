/* PARKED at triage (0 round trips): m2c draft has multiple unresolved "?32"
 * globals and an opaque local object `sp50` (unknown size, C++ virtual call
 * through sp50.unkC0->unk14) reinterpreted through s128 quadword casts to
 * build a vector constant. Needs a raw-asm read to pin the local's real
 * size/layout before this is worth compiling -- deferred to preserve lane
 * throughput. See asm/matchings/main/DrawModelPreview_28be80.s. */
/* s49m: 24 bad (right length) */
#include "types.h"
#include "vec.h"

struct Cam {
    u8 pad0[0xC0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void f14(f32);
};

typedef struct V4 {
    f32 x, y, z, w;
} V4;

extern V4 D_0047EB10 __attribute__((section(".sdata")));
extern V4 D_0047EB20 __attribute__((section(".sdata")));

extern "C" void CameraObjCtor_177430(Cam *);
extern "C" void CameraTweenStep_1771a0(Cam *, f32);
extern "C" void DrawModelWithCamera_28bf80(f32, s32, f32, Cam *);

#define VEC(c, o) (*(Vec4 *)((u8 *)(c) + (o)))

extern "C" void DrawModelPreview_28be80(s32 arg0, f32 x, f32 y)
{
    Vec4 buf[0x19];
    Vec4 b;
    Vec4 a;
    Vec4 *p;

    if (arg0 == 0) {
        return;
    }
    CameraObjCtor_177430((Cam *)buf);
    ((Cam *)buf)->f14(42.5f);
    { f32 *pb = (f32 *)&b; pb[0] = D_0047EB20.x; pb[1] = D_0047EB20.y; pb[2] = D_0047EB20.z; pb[3] = D_0047EB20.w; }
    p = &b;
    p->z = 90.0f;
    p->x = 0.0f;
    p->y = 0.0f;
    { f32 *pa = (f32 *)&a; pa[0] = D_0047EB10.x; pa[1] = D_0047EB10.y; pa[2] = D_0047EB10.z; pa[3] = D_0047EB10.w; }
    p = &a;
    p->z = -500.0f;
    p->x = 0.0f;
    p->y = 0.0f;
    VEC(buf, 0xF0) = b;
    VEC(buf, 0x60) = b;
    VEC(buf, 0xE0) = a;
    VEC(buf, 0x50) = a;
    CameraTweenStep_1771a0((Cam *)buf, -1.0f);
    DrawModelWithCamera_28bf80(x, arg0, y, (Cam *)buf);
}
