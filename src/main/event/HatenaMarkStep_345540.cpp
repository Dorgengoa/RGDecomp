#include "types.h"

typedef f32 Vec4[4] __attribute__((aligned(16)));

typedef struct Mdl {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x20];
    s8 b28;
    u8 pad29[0x67];
    f32 x90;
    f32 y90;
    f32 z90;
} Mdl;

typedef struct Own {
    u8 pad0[0x448];
    f32 f448;
} Own;

typedef struct Chr {
    u8 pad0[0x4CC];
    f32 f4CC;
} Chr;

typedef struct Fx {
    Own *p0;
    s32 p4;
    Mdl *p8;
    u8 bC;
    u8 padD[0x13];
    Vec4 v20;
    Vec4 v30;
    Vec4 v40;
    f32 f50;
    u8 pad54[0x10];
    f32 f64;
    u8 pad68[8];
    f32 f70;
    f32 f74;
    f32 f78;
    u8 pad7C[4];
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    u8 pad90[4];
    f32 f94;
    f32 f98;
    f32 f9C;
    u8 bA0;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    s16 hA2;
} Fx;

extern "C" {
extern f32 D_0045B078[];

extern f64 Sin_128880(f64);
extern void VecSubInPlace_13e050(f32 *, f32 *);
extern void VecAddInPlace_13e070(f32 *, f32 *);
extern void FrameSetDirty_14a5e0(Mdl *);
extern s32 ModelGetRootFrame_1511a0(Chr *);
extern Chr *ObjRecGetLiveObject_1c4a90(s32, s32);
extern f32 AngleWrap_1cbf30(f32);
extern s32 GetCurrentScene_1f5be0(void);
extern void sceVu0CopyVector(void *, void *);

s32 HatenaMarkStep_345540(Fx *o)
{
    f32 s;
    f32 c;
    u8 k;
    f32 t;
    Chr *p;
    Mdl *q;

    if (o->bC == 2) {
        return 1;
    }
    if (o->f50 <= 2000.0f) {
        o->bA0 = 1;
    } else {
        o->bA0 = 0;
    }
    s = Sin_128880(o->f94);
    c = Sin_128880(o->f98);
    o->v30[1] = 4.0f * s;
    s = s / 3.0f;
    o->f94 += 0.1f;
    if (o->f94 >= 3.14f) {
        o->f94 = 0.0f;
    }
    if (o->b3 != 2) {
        o->f98 += 0.05f;
        if (o->f98 >= 3.14f) {
            o->f98 = 0.0f;
        }
    }
    k = o->b3;
    if (k == 0) {
        o->f70 = o->f78 = 0.7f + c / 2.0f;
        o->f74 = 0.5f;
        o->f9C = 0.1f;
    } else if (k == 1) {
        o->f70 += o->f9C;
        o->f74 -= 0.07f;
        o->f78 += o->f9C;
        o->f9C *= 1.2f;
        if (o->f74 <= 0.0f) {
            o->f70 = 0.0f;
            o->f74 = 0.0f;
            o->f78 = 0.0f;
            o->f9C = 0.1f;
        }
    } else if (k == 2) {
        o->f70 += 0.099f;
        o->f78 += 0.099f;
        o->f74 += 0.1f;
        if (!(o->f74 < 0.5f)) {
            o->f74 = 0.5f;
            o->b3 = false;
            o->f98 = 0.0f;
        }
    }
    k = o->b2;
    if (k == 0) {
        o->b0 = 0;
        if (o->bC == 1) {
            o->f80 = o->f84 = o->f88 = 0.3f + s / 2.0f;
        } else {
            o->f80 = o->f84 = o->f88 = 0.7f + s;
        }
    } else if (k == 1) {
        Vec4 v = {0.1f, 0.1f, 0.1f, 1.0f};
        o->b0 = 1;
        o->b3 = 1;
        VecSubInPlace_13e050(&o->f80, v);
        if (o->f80 <= 0.0f) {
            o->f80 = o->f84 = o->f88 = 0.0f;
            o->f8C = 1.0f;
            o->b2 = 2; /* = 0: mwcc folds only a NON-zero bitfield constant (daddu v1,$0,$0) */
            if (o->bC == 0 || o->bC == 3) {
                o->f70 = 0.0f;
                o->f74 = 0.0f;
                o->f78 = 0.0f;
                o->f9C = 0.1f;
                o->b3 = 2; /* = 0, folded form */
            }
        }
    } else if (k == 2) {
        o->b0 = 0;
        Vec4 v2 = {0.1f, 0.1f, 0.1f, 1.0f};
        VecAddInPlace_13e070(&o->f80, v2);
        if (o->bC == 1) {
            t = 0.3f + (f32)(s / 2.0f);
            if (!(o->f80 < t)) {
                o->f80 = o->f84 = o->f88 = t;
                o->f8C = 1.0f;
                o->b2 = false;
            }
        } else {
            t = 0.7f + s;
            if (!(o->f80 < t)) {
                o->f88 = o->f84 = o->f80 = t;
                o->f8C = 1.0f;
                o->b2 = false;
            }
        }
    }
    if (o->bC == 1 && o->b0 != 1) {
        sceVu0CopyVector(o->v20, o->v40);
        p = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), 0);
        if (p != 0) {
            o->v20[1] += (f32)(5.0 + 0.1 * p->f4CC);
        } else {
            o->v20[1] += 37.0f;
        }
        {
            s32 r = ModelGetRootFrame_1511a0(p);
            q = o->p8;
            q->b28 = 1;
            q->w4 = r;
            FrameSetDirty_14a5e0(q);
        }
        {
            Vec4 c3 = {0.0f, 37.0f, 0.0f, 1.0f};
            q = o->p8;
            q->x90 = c3[0];
            q->y90 = c3[1];
            q->z90 = c3[2];
            FrameSetDirty_14a5e0(q);
        }
        t = 1.0f;
        if (o->hA2 != 0) {
            t = 0.0f;
        }
        o->p0->f448 = t;
    } else {
        o->v20[2] = 0.0f;
        o->v20[1] = 0.0f;
        o->v20[0] = 0.0f;
        o->v20[1] = 5.0f;
        o->v20[3] = 1.0f;
        q = o->p8;
        if (q->b28 != 0) {
            q->w4 = 0;
        }
        {
            s32 r2 = o->p4;
            q = o->p8;
            q->b28 = 1;
            q->w4 = r2;
            FrameSetDirty_14a5e0(q);
        }
        {
            Vec4 c4 = {0.0f, 0.0f, 0.0f, 1.0f};
            q = o->p8;
            q->x90 = c4[0];
            q->y90 = c4[1];
            q->z90 = c4[2];
            FrameSetDirty_14a5e0(q);
        }
        o->p0->f448 = 1.0f;
    }
    o->f64 = AngleWrap_1cbf30(o->f64 + 6.2831855f / (10.0f * D_0045B078[0]));
    return 0;
}

}
