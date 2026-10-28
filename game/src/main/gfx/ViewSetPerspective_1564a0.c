/* rgp:protos */
#define RGP_SELF_ViewSetPerspective_1564a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct M4 { V4 r[4]; } __attribute__((aligned(16))) M4;
typedef struct Prm {
    f32 fov;
    u8 pad4[8];
    f32 m20;
    f32 m24;
    u8 pad28[0x18];
    f32 aspect;
    u8 pad44[4];
    f32 near;
    f32 far;
} Prm;
typedef struct Cam {
    u8 pad0[0x14];
    Prm prm;
    u8 pad50[0xA0];
    M4 proj;
    M4 m130;
    u8 pad170[0x90];
    M4 m200;
    f32 m240;
    f32 m244;
    u8 pad248[8];
    M4 m250;
    u8 pad290[0x80];
    V4 pl[12];
    M4 m3D0;
    M4 m410;
    M4 m450;
    M4 m490;
} Cam;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ViewSetPerspective_1564a0(Cam *c, f32 fov, f32 aspect, f32 a2, f32 a3, f32 near, f32 far)
{
    M4 m __attribute__((aligned(16)));
    M4 m2 __attribute__((aligned(16)));
    Prm *p;
    s32 i;

    p = &c->prm;
    c->prm.fov = fov;
    c->prm.m20 = a2;
    c->prm.m24 = a3;
    c->prm.near = near;
    c->prm.far = far;
    c->prm.aspect = aspect;
    MtxIdentity_13d2e0(&c->proj);
    c->proj.r[0].x = aspect * (1.0f / Tanf_1290b8(p->fov / 2.0f));
    c->proj.r[1].y = 1.0f / Tanf_1290b8(p->fov / 2.0f);
    c->proj.r[2].z = -(p->far + p->near) / (p->far - p->near);
    c->proj.r[3].z = -2.0f * p->far * p->near / (p->far - p->near);
    c->proj.r[2].w = -1.0f;
    c->proj.r[3].w = 0.0f;
    MtxMul_13d240(&c->m200, &c->m130, &c->proj);
    sceVu0TransposeMatrix(&m, &c->proj);
    VecAdd_13be20(&c->pl[0], &m.r[3], &m.r[2]);
    VecScale_13be00(&c->pl[0], &c->pl[0], 1.0f / VecLength_13d4a0(&c->pl[0]));
    VecSub_13be40(&c->pl[1], &m.r[3], &m.r[2]);
    VecScale_13be00(&c->pl[1], &c->pl[1], 1.0f / VecLength_13d4a0(&c->pl[1]));
    VecSub_13be40(&c->pl[2], &m.r[3], &m.r[0]);
    VecScale_13be00(&c->pl[2], &c->pl[2], 1.0f / VecLength_13d4a0(&c->pl[2]));
    VecAdd_13be20(&c->pl[3], &m.r[3], &m.r[0]);
    VecScale_13be00(&c->pl[3], &c->pl[3], 1.0f / VecLength_13d4a0(&c->pl[3]));
    VecSub_13be40(&c->pl[4], &m.r[3], &m.r[1]);
    VecScale_13be00(&c->pl[4], &c->pl[4], 1.0f / VecLength_13d4a0(&c->pl[4]));
    VecAdd_13be20(&c->pl[5], &m.r[3], &m.r[1]);
    VecScale_13be00(&c->pl[5], &c->pl[5], 1.0f / VecLength_13d4a0(&c->pl[5]));
    sceVu0TransposeMatrix(&c->m3D0, (M4 *)&c->pl[2]);
    sceVu0TransposeMatrix(&c->m410, (M4 *)&c->pl[0]);
    ((u128 *)&c->m250)[0] = ((u128 *)&c->proj)[0];
    ((u128 *)&c->m250)[1] = ((u128 *)&c->proj)[1];
    ((u128 *)&c->m250)[2] = ((u128 *)&c->proj)[2];
    ((u128 *)&c->m250)[3] = ((u128 *)&c->proj)[3];
    for (i = 0; i < 4; i++) {
        c->m250.r[i].x *= c->m240;
        c->m250.r[i].y *= c->m244;
    }
    sceVu0TransposeMatrix(&m2, &c->m250);
    VecAdd_13be20(&c->pl[6], &m2.r[3], &m2.r[2]);
    VecScale_13be00(&c->pl[6], &c->pl[6], 1.0f / VecLength_13d4a0(&c->pl[6]));
    VecSub_13be40(&c->pl[7], &m2.r[3], &m2.r[2]);
    VecScale_13be00(&c->pl[7], &c->pl[7], 1.0f / VecLength_13d4a0(&c->pl[7]));
    VecSub_13be40(&c->pl[8], &m2.r[3], &m2.r[0]);
    VecScale_13be00(&c->pl[8], &c->pl[8], 1.0f / VecLength_13d4a0(&c->pl[8]));
    VecAdd_13be20(&c->pl[9], &m2.r[3], &m2.r[0]);
    VecScale_13be00(&c->pl[9], &c->pl[9], 1.0f / VecLength_13d4a0(&c->pl[9]));
    VecSub_13be40(&c->pl[10], &m2.r[3], &m2.r[1]);
    VecScale_13be00(&c->pl[10], &c->pl[10], 1.0f / VecLength_13d4a0(&c->pl[10]));
    VecAdd_13be20(&c->pl[11], &m2.r[3], &m2.r[1]);
    VecScale_13be00(&c->pl[11], &c->pl[11], 1.0f / VecLength_13d4a0(&c->pl[11]));
    sceVu0TransposeMatrix(&c->m450, (M4 *)&c->pl[8]);
    sceVu0TransposeMatrix(&c->m490, (M4 *)&c->pl[6]);
}
