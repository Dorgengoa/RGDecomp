/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

typedef struct Prm {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
} Prm;

class Base {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Prm * GetPrm(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Prm *, (void *, int, int, int), 0x48, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

class Obj : public Base {
public:
    u8 padC4[0xE0 - 0xC4];
    Vec4 xE0;
    Vec4 xF0;
    u8 pad100[0x120 - 0x100];
    u8 x120[0x230 - 0x120];
    Vec4 x230;
    s32 x240;
};

extern "C" {
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void VecAddInPlace_13e070(Vec4 *, u8 *);
s32 MeshRaycastWrapper_16f610(s32, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
s32 CameraCollideGroundMaybe_160500(Obj *self, s32 arg1, s32 arg2, int rgp_a3);
}

static inline f32 Lerp(f32 a, f32 b, f32 t) {
    return a + t * (b - a);
}

static inline void Calc(Prm *p, f32 d, Vec4 *a, Vec4 *b) {
    f32 dy = b->y - a->y;
    f32 l = Lerp(p->x8, p->xC, (d - p->x0) / (p->x4 - p->x0));
    p->x10 = -(l + dy);
}

s32 CameraCollideGroundMaybe_160500(Obj *self, s32 arg1, s32 arg2, int rgp_a3) {
    Vec4 vB0 __attribute__((aligned(16)));
    Vec4 vA0 __attribute__((aligned(16)));
    Vec4 v90 __attribute__((aligned(16)));
    Vec4 v80 __attribute__((aligned(16)));
    Vec4 v70 __attribute__((aligned(16)));
    Vec4 v60 __attribute__((aligned(16)));
    Prm *p;
    s32 ok;

    p = self->GetPrm((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3));
    {
        Vec4 *pe = &self->xE0;
        if (self->x240 != 0) {
            vB0 = self->x230;
            VecAddInPlace_13e070(&vB0, self->x120);
        } else {
            vB0 = *pe;
        }
    }
    v90 = self->xF0;
    vA0 = v90;
    v90.y -= p->x24;
    ok = 0;
    if (MeshRaycastWrapper_16f610(arg1, arg2, &vA0, &v90, &v80, 1, 0) >= 0) {
        vA0.y = v80.y + p->x24;
        self->xF0 = vA0;
        Calc(p, VecDistance_13d3d0(&vA0, &vB0), &vA0, &vB0);
        ok = 1;
    } else {
        f32 h = p->x18;
        if (vA0.y - vB0.y < h) {
            vA0.y = vB0.y + h;
            self->xF0 = vA0;
        }
    }
    vA0 = self->xF0;
    v70 = vA0;
    v70.y += 10.0f;
    if (MeshRaycastWrapper_16f610(arg1, arg2, &vA0, &v70, &v60, 1, 0) >= 0) {
        vA0.y = v60.y - 10.0f;
        self->xF0 = vA0;
        Calc(p, VecDistance_13d3d0(&vA0, &vB0), &vA0, &vB0);
        ok = 1;
    }
    return ok;
}
