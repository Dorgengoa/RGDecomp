/* rgp:protos */
#define RGP_SELF_BattleEffectParticleDraw_2d4400 1
#define RGP_SELF_setv 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct IV4 {
    s32 x, y, z, w;
} IV4;

typedef struct Col {
    f32 r, g, b, a;
} Col;

typedef struct Obj {
    u8 pad0[0x24];
    f32 size;       /* 0x24 */
    u8 pad28[8];
    f32 alpha;      /* 0x30 */
    u8 pad34[4];
    s32 type;       /* 0x38 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u128 D_0047EE80 __attribute__((section(".sdata")));
extern u128 D_0047EE90 __attribute__((section(".sdata")));
extern u128 D_0047EEA0 __attribute__((section(".sdata")));
extern u128 D_0047EEB0 __attribute__((section(".sdata")));
extern u128 D_0047EEC0 __attribute__((section(".sdata")));

static inline void setv(IV4 *v, s32 x, s32 y, s32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = 1;
}

void BattleEffectParticleDraw_2d4400(s32 unused, s32 dl, Obj *o)
{
    s32 t0[4] __attribute__((aligned(16)));
    s32 t1[4] __attribute__((aligned(16)));
    s32 t2[4] __attribute__((aligned(16)));
    s32 t3[4] __attribute__((aligned(16)));
    s32 t4[4] __attribute__((aligned(16)));
    IV4 a __attribute__((aligned(16)));
    IV4 q __attribute__((aligned(16)));
    IV4 r __attribute__((aligned(16)));
    IV4 b __attribute__((aligned(16)));
    Col col __attribute__((aligned(16)));
    s32 *t;
    s32 *p;
    f32 w;

    *(u128 *)t1 = D_0047EE90;
    *(u128 *)t2 = D_0047EEA0;
    *(u128 *)t3 = D_0047EEB0;
    *(u128 *)t4 = D_0047EEC0;
    p = t0;
    *(u128 *)p = D_0047EE80;
    if (o->type == 0) {
        t = p;
        col.b = 0.0f;
        col.r = 255.0f;
        col.g = 96.0f;
        col.a = 255.0f * o->alpha;
        w = 15.0f * o->size;
    }
    if (o->type == 1) {
        col.g = 128.0f;
        t = t1;
        col.r = 64.0f;
        col.b = 64.0f;
        col.a = 255.0f * o->alpha;
        w = 15.0f * o->size;
    }
    if (o->type == 2) {
        col.r = 96.0f;
        t = t2;
        col.g = 64.0f;
        col.b = 64.0f;
        col.a = 255.0f * o->alpha;
        w = 15.0f * o->size;
    }
    if (o->type == 3) {
        col.b = 0.0f;
        col.r = 255.0f;
        t = t3;
        col.g = 32.0f;
        col.a = 255.0f * o->alpha;
        w = 2.0f * o->size;
    }
    if (o->type == 4) {
        col.g = 128.0f;
        t = t4;
        col.r = 64.0f;
        col.b = 64.0f;
        col.a = 255.0f * o->alpha;
        w = 5.0f * o->size;
    }
    if (CameraProjectBillboardRect_15cde0(&a, &b, w, w, o) == 0) {
        return;
    }
    GsPktSetRGBAQVec_13edd0(dl, &col);
    GsPktSetUV_13ed60(dl, t[0], t[1]);
    GsPktSetXYZVecI_13eeb0(dl, &a);
    setv(&q, b.x, a.y, a.z);
    GsPktSetUV_13ed60(dl, t[0] + t[2], t[1]);
    GsPktSetXYZVecI_13eeb0(dl, &q);
    setv(&r, a.x, b.y, a.z);
    GsPktSetUV_13ed60(dl, t[0], t[1] + t[3]);
    GsPktSetXYZVecI_13eeb0(dl, &r);
    setv(&q, b.x, a.y, a.z);
    GsPktSetUV_13ed60(dl, t[0] + t[2], t[1]);
    GsPktSetXYZVecI_13eeb0(dl, &q);
    setv(&r, a.x, b.y, a.z);
    GsPktSetUV_13ed60(dl, t[0], t[1] + t[3]);
    GsPktSetXYZVecI_13eeb0(dl, &r);
    GsPktSetUV_13ed60(dl, t[0] + t[2], t[1] + t[3]);
    GsPktSetXYZVecI_13eeb0(dl, &b);
}
