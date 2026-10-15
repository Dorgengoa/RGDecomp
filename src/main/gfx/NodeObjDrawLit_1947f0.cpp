#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_loop_invariants off
#pragma opt_propagation off
#include "types.h"

typedef unsigned int u128 __attribute__((mode(TI)));

typedef union {
    f32 f[4];
    u128 q;
} Vec;

typedef struct {
    Vec r[4];
} Mat;

struct State {
    s32 a;
    s32 b;
    u8 pad[0x18];
    Vec v1[4];
    Vec v2[4];
    u8 pad2[0x100];
    void Get(s32 i, Vec *c, Vec *d) {
        Vec *r;
        if (i >= 0 && i < 4) {
            r = (Vec *)this + i;
            c->q = r[2].q;
            c->f[3] = 0.0f;
            d->q = r[6].q;
        }
    }
    void Set(s32 i, Vec *c, Vec *d) {
        Vec *r;
        if (i >= 0 && i < 4) {
            r = (Vec *)this + i;
            r[2].q = c->q;
            r[2].f[3] = 0.0f;
            r[6].q = d->q;
        }
    }
};

struct Base68 {
    u8 p0[0x34];
    struct Obj *owner;
    s32 m38;
    u32 flags;
    u8 p40[0x10];
    s32 m50;
    u8 p54[0x10];
    f32 scale;
};

struct Obj : public Base68 {
public:
    virtual void v0();
    virtual f32 Scale();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual s32 Ok();
    virtual s32 DrawA();
    virtual s32 DrawB();
    u8 p6c[0x18];
    f32 f84;
    f32 f88;
    u8 p8c[8];
    s32 *list94;
    u8 p98[0x78];
    s32 m110;
    u8 list114[0x14];
    s32 m128;
    s32 m12C;
    u8 p130[0x14];
    s32 m144;
    f32 f148;
    s32 m14C;
};

extern "C" {
extern void VecMulXyz_13bd20(Vec *, Vec *, Vec *);
extern void VecNormalize_13bd90(Vec *, Vec *);
extern void VecScale_13be00(Vec *, Vec *, f32);
extern f32 VecLength_13d4a0(Vec *);
extern void VecAddInPlace_13e070(Vec *, Vec *);
extern void LightStateSetCurrent_142920(s32, s32);
extern void LightStateEmitOnce_142950(s32);
extern s32 LightStatePush_1429f0(s32, State *, s32);
extern void LightStateInit_156b50(State *);
extern void LightStateSetPointLight_15ca80(s32, Vec *, Vec *, f32);
extern void LightStateGetAmbient_15cb10(Vec *);
extern void LightStateSetAmbient_15cb30(Vec *);
extern void LightStateGetMatrices_15cb50(Mat *, Mat *);
extern void LightStateSetDirLight_15cbb0(s32, Vec *, Vec *);
extern s32 CameraGetLightModeMaybe_15cca0(void);
extern void CameraSetLightModeMaybe_15ccc0(s32);
extern s32 GetDrawCtx_15de80(void);
extern void NodeTransformDir_186060(Obj *, Vec *, Vec *);
extern void NodeTransformPoint_1860b0(Obj *, Vec *, Vec *);
extern void NodeGetTranslation_186650(u8 *, Vec *);
extern f32 LightFlickerScale_18e2c0(u8 *, s32);
extern u8 *FuncDataTableIterNext_1908b0(u8 *);
extern void FuncDataTableIterBegin_1908e0(u8 *, s32);
extern s32 InRangeWrap_1922b0(f32, f32, f32);
}

#define SELF(o) (*(s32 *)((u8 *)self + (o)))

extern "C" s32 NodeObjDrawLit_1947f0(Obj *self, s32 arg1) {
    State st;
    Vec a;
    Vec b;
    Vec c;
    Vec e;
    Vec d;
    Vec t160;
    Vec t150;
    Vec t140;
    Vec t130;
    Mat mf0;
    Mat mb0;
    Vec ta0;
    s32 ctx;
    s32 h;
    s32 n1;
    s32 n0;
    s32 save;
    s32 i;
    u8 *it;
    f32 len;
    Vec *vp;
    f32 s;
    f32 k;
    f32 w;
    s32 sum;
    s32 *node;
    Obj *o;

    ctx = GetDrawCtx_15de80();
    if (self->Ok() == 0) {
        return 0;
    }
    st.a = -1;
    st.b = 0;
    h = 0;
    LightStateInit_156b50(&st);
    if (self->m128 != 0) {
        LightStateInit_156b50(&st);
        h = LightStatePush_1429f0(ctx, &st, 0);
    }
    n0 = self->m144 - 1;
    n1 = 3;
    save = CameraGetLightModeMaybe_15cca0();
    if (self->m110 != 0) {
        if (h == 0) {
            h = LightStatePush_1429f0(ctx, &st, 1);
        }
        vp = (Vec *)self->m110;
        a.q = vp[0].q;
        b.q = vp[1].q;
        i = 0;
        do {
            st.Get(i, &c, &d);
            { f32 h_ = 0.5f; c.f[1] = c.f[1] * h_; }
            {
                f32 cx = c.f[0];
                if (cx > 0.0f) {
                    e.f[0] = (1.0f - b.f[0]) * cx;
                } else {
                    e.f[0] = (1.0f - a.f[0]) * cx;
                }
            }
            {
                f32 cz = c.f[2];
                if (cz > 0.0f) {
                    e.f[2] = (1.0f - b.f[2]) * cz;
                } else {
                    e.f[2] = (1.0f - a.f[2]) * cz;
                }
            }
            e.f[1] = c.f[1];
            len = VecLength_13d4a0(&e);
            { Vec *p_; f32 l_ = len / VecLength_13d4a0(&c); p_ = &d; VecScale_13be00(p_, p_, l_); }
            st.Set(i, &c, &d);
            i++;
        } while (i < 4);
    }
    if (self->m12C != 0) {
        CameraSetLightModeMaybe_15ccc0(0);
    }
    if (*(u32 *)self->list114 & 0x20) {
        FuncDataTableIterBegin_1908e0(self->list114, 4);
        while ((it = FuncDataTableIterNext_1908b0(self->list114)) != 0) {
            if (*(s32 *)(it + 0x48) == 0) {
                continue;
            }
            if (h == 0) {
                h = LightStatePush_1429f0(ctx, &st, 1);
            }
            s = 1.0f;
            s *= LightFlickerScale_18e2c0(it, self->m14C);
            switch (*(s32 *)(it + 0x78)) {
            case 0:
                if (n1 >= 0) {
                    NodeGetTranslation_186650(it, &t130);
                    NodeTransformDir_186060(self, &t160, &t130);
                    { Vec *p_ = &t160; VecNormalize_13bd90(p_, p_); }
                    VecScale_13be00(&t140, (Vec *)(it + 0x60), s);
                    t140.f[3] = 0.0f;
                    LightStateSetDirLight_15cbb0(n1, &t160, &t140);
                    n1--;
                }
                break;
            case 1:
                LightStateGetAmbient_15cb10(&t150);
                t150.f[0] = *(f32 *)(it + 0x60) * s;
                t150.f[1] = *(f32 *)(it + 0x64) * s;
                t150.f[2] = *(f32 *)(it + 0x68) * s;
                LightStateSetAmbient_15cb30(&t150);
                break;
            case 2:
                CameraSetLightModeMaybe_15ccc0(1);
                if (n0 >= 0 && *(s32 *)(it + 0x88) == 0) {
                    NodeGetTranslation_186650(it, &t130);
                    NodeTransformPoint_1860b0(self, &t160, &t130);
                    { f32 r_ = LightFlickerScale_18e2c0(it, 0); VecScale_13be00(&ta0, (Vec *)(it + 0x60), r_ * s); }
                    LightStateSetPointLight_15ca80(n0, &t160, &ta0, *(f32 *)(it + 0x70));
                    n0--;
                }
                break;
            case 3:
                LightStateGetAmbient_15cb10(&t150);
                w = t150.f[3];
                VecScale_13be00(&t140, (Vec *)(it + 0x60), s);
                VecAddInPlace_13e070(&t150, &t140);
                t150.f[3] = w;
                LightStateSetAmbient_15cb30(&t150);
                break;
            case 4:
                it += 0x60;
                LightStateGetMatrices_15cb50(&mf0, &mb0);
                LightStateGetAmbient_15cb10(&t150);
                { Vec *p_ = &mb0.r[0]; VecMulXyz_13bd20(p_, p_, (Vec *)it); }
                { Vec *p_ = &mb0.r[1]; VecMulXyz_13bd20(p_, p_, (Vec *)it); }
                { Vec *p_ = &mb0.r[2]; VecMulXyz_13bd20(p_, p_, (Vec *)it); }
                { Vec *p_ = &mb0.r[3]; VecMulXyz_13bd20(p_, p_, (Vec *)it); }
                { Vec *p_ = &t150; VecMulXyz_13bd20(p_, p_, (Vec *)it); }
                LightStateGetMatrices_15cb50(&mf0, &mb0);
                LightStateSetAmbient_15cb30(&t150);
                break;
            }
        }
    }
    if (h != 0) {
        LightStateEmitOnce_142950(ctx);
    }
    k = self->scale;
    if (self->m50 != 0) {
        k *= self->Scale();
    }
    sum = 0;
    for (node = (s32 *)self->list94; node != 0; node = (s32 *)*node) {
        o = (Obj *)node[4];
        if (InRangeWrap_1922b0(self->f148, o->f84, o->f88) != 0) {
            o->flags &= ~0x40000000;
        } else {
            o->flags |= 0x40000000;
        }
        w = o->scale;
        o->owner = self;
        o->m38 = 0;
        o->scale = w * k;
        if (arg1 == 0) {
            sum += o->DrawA();
        } else {
            sum += o->DrawB();
        }
        o->owner = 0;
        o->m38 = 0;
        o->scale = w;
    }
    if (h != 0) {
        LightStateSetCurrent_142920(ctx, h);
    }
    CameraSetLightModeMaybe_15ccc0(save);
    return sum;
}
