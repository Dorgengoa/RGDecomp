#include "types.h"
#include "vec.h"

struct V176e10 { f32 x, y, z, w; };
struct M176e10 { f32 m[4][4]; };

class VC176 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void g(u128 * a0) { VCM(void, (void *, u128 *), 0x94, a0); }
    void h(u128 * a0) { VCM(void, (void *, u128 *), 0x98, a0); }
};
struct O176e10 { u8 pad[0xF0]; u128 unkF0; };

extern "C" {
void VecAdd_13be20(u128 *, u128 *, V176e10 *);
f32 WrapAngle_13c050(f32);
void MtxMulVec4_13c900(V176e10 *, M176e10 *, V176e10 *);
void MtxIdentity_13d2e0(M176e10 *);
f32 VecDistanceXZ_13d390(u128 *, u128 *);
void sceVu0RotMatrixY(M176e10 *, M176e10 *, f32);

void CameraSetEyeYaw_176e10(O176e10 *arg0, f32 f)
{
    u128 sp90;
    u128 sp80;
    V176e10 v __attribute__((aligned(16)));
    M176e10 m __attribute__((aligned(16)));
    f32 d;
    f32 dy;
    u8 *p;
    u32 n;

    ((VC176 *)arg0)->g(&sp80);
    ((VC176 *)arg0)->h(&sp90);
    d = VecDistanceXZ_13d390(&sp80, &sp90);
    dy = ((f32 *)&sp90)[1] - ((f32 *)&sp80)[1];
    p = (u8 *)&v;
    n = 16;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v.y = dy;
    v.z = d;
    MtxIdentity_13d2e0(&m);
    sceVu0RotMatrixY(&m, &m, WrapAngle_13c050(f));
    MtxMulVec4_13c900(&v, &m, &v);
    VecAdd_13be20(&sp90, &sp80, &v);
    arg0->unkF0 = sp90;
}
}
