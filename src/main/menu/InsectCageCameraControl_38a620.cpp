#include "types.h"

class Obj {
public:
    u8 pad[0xC0];
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v64(f32);
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void vA4(f32 *);
    virtual void v0A8();
    virtual void v0AC();
    virtual void vB0(f32 *);
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void vC8(f32);
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
    f32 v[4];
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
