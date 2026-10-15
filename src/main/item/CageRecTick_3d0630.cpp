#include "types.h"

struct R3d0630 {
    s16 h0;
    s16 h2;
    s16 h4pad;
};

struct V3d0630 {
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
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual R3d0630 *v070(s32);
};

struct M3d0630 {
    u8 pad0[8];
    V3d0630 *p8;
};

struct G3d0630 {
    u8 pad0[0x40];
    M3d0630 *p40;
};

struct E3d0630 {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 bE0 : 1;
    u8 bE1 : 7;
};

struct O3d0630 {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s32 wC;
    u8 pad10[0x7EC - 0x10];
    f32 f7EC;
};

struct A3d0630 {
    u8 pad0[0x18];
    O3d0630 *p18;
};

extern "C" f32 RandFloat_13c010(...);
extern "C" E3d0630 *CageRecGetEntry_3d0880(A3d0630 *, s32);
extern "C" s32 InsectColorForSpeciesMaybe_3d2700(s32, s32);
extern G3d0630 *D_004838EC;

extern "C" s32 CageRecTick_3d0630(A3d0630 *arg0, f32 x)
{
    s32 n;
    s32 i;
    E3d0630 *e;
    s32 v;
    s32 k;
    R3d0630 *r;

    if (!(arg0->p18->f7EC < 0.0f)) {
        arg0->p18->f7EC += x;
        if (arg0->p18->h4 <= 0 && arg0->p18->h2 > 0) {
            n = arg0->p18->hA;
            for (i = 0; i < n; i++) {
                e = CageRecGetEntry_3d0880(arg0, i);
                if (e == 0) {
                    continue;
                }
                if (e->bE0) {
                    continue;
                }
                if (arg0->p18->f7EC < (f32)e->h2) {
                    continue;
                }
                e->bE0 = true;
                if (e->h4 == 1) {
                    arg0->p18->h4 = e->hA;
                    v = e->hC;
                    if (v >= 0 && v < 10) {
                        arg0->p18->wC = v;
                    } else if (v == 10) {
                        arg0->p18->wC = (s32)(7.0f * RandFloat_13c010());
                    } else {
                        arg0->p18->wC = (s32)(3.0f * RandFloat_13c010()) + 7;
                    }
                    arg0->p18->h2 = -1;
                    k = 0;
                    r = D_004838EC->p40->p8->v070(arg0->p18->h4);
                    if (r != 0) {
                        k = r->h4pad;
                    }
                    arg0->p18->wC = InsectColorForSpeciesMaybe_3d2700(k, arg0->p18->wC);
                } else if (*(u8 *)&e->hA & 1) {
                    arg0->p18->h2 = -1;
                }
                break;
            }
        }
    }
    return 1;
}
