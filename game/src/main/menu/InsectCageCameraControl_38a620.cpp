#include "types.h"

class Obj {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v64(f32 a0) { VCM(void, (void *, f32), 0x64, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void vA4(f32 * a0) { VCM(void, (void *, f32 *), 0xA4, a0); }
    
    
    void vB0(f32 * a0) { VCM(void, (void *, f32 *), 0xB0, a0); }
    
    
    
    
    
    void vC8(f32 a0) { VCM(void, (void *, f32), 0xC8, a0); }
};

extern "C" {
extern f32 PadGetAnalogRYNorm_183b90(void *arg0);
extern f32 PadGetAnalogRXNorm_183c30(void *arg0);
extern Obj *GetCurrentSceneCamera_389d40(void);
extern f32 D_0047D5B8;
extern f32 D_0047D5BC;
extern volatile f32 D_0047D5C0;
extern volatile f32 D_0047D5C4;
extern f32 D_00483350;
extern f32 D_00483354;
extern u8 D_004B2570[];
}

extern "C" void InsectCageCameraControl_38a620(void)
{
    f32 v[4] __attribute__((aligned(16)));
    f32 x;
    f32 y;
    f32 t;
    Obj *o;

    o = GetCurrentSceneCamera_389d40();
    if (o == 0) {
        return;
    }
    x = PadGetAnalogRYNorm_183b90(D_004B2570);
    y = PadGetAnalogRXNorm_183c30(D_004B2570);
    if (x) {
        t = D_00483350 + D_0047D5B8 * -x;
        D_00483350 = t;
        if (!(t < 15.0f)) {
            D_00483350 = 15.0f;
        } else if (t < 0.0f) {
            D_00483350 = -0.0f;
        }
    }
    if (y) {
        t = D_00483354 + D_0047D5BC * y;
        D_00483354 = t;
        if (!(t < D_0047D5C0)) {
            D_00483354 = D_0047D5C0;
        } else if (t < D_0047D5C4) {
            D_00483354 = D_0047D5C4;
        }
    }
    o->vA4(v);
    v[1] = 6.0f + D_00483350;
    o->vB0(v);
    o->v64(D_00483354);
    o->vC8(-1.0f);
}
