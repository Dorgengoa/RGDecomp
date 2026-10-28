/* rgp:protos */
#define RGP_SELF_EvMapObjPointStep_3642d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj {
    Vec4 pos;       /* 0x00 */
    Vec4 vel;       /* 0x10 */
    f32 prev[3];    /* 0x20 */
    f32 nrm[3];     /* 0x2C */
    s32 hit;        /* 0x38 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D244;
extern f32 D_0047D27C;
extern f32 D_0047D2A0;
extern f32 D_0047D2A4;
typedef struct F4 { f32 a, b, c, d; } F4;
extern F4 D_0047F900 __attribute__((section(".sdata")));

void EvMapObjPointStep_3642d0(Obj *o, s32 a, s32 b, f32 t) { RG_VU0_FRAME;
    Vec4 g __attribute__((aligned(16)));
    Vec4 old __attribute__((aligned(16)));
    Vec4 hp __attribute__((aligned(16)));
    Vec4 n __attribute__((aligned(16)));
    Vec4 v80 __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 p __attribute__((aligned(16)));
    Vec4 r __attribute__((aligned(16)));
    f32 len;

    *(F4 *)&g = D_0047F900;
    VecAdd_13be20(&o->vel, &o->vel, &g);
    VecScale_13be00(&o->vel, &o->vel, D_0047D27C);
    len = VecLength_13d4a0(&o->vel);
    if (!(len <= D_0047D2A0)) {
        VecScale_13be00(&o->vel, &o->vel, D_0047D2A0 / len);
    }
    old = o->pos;
    VecAdd_13be20(&o->pos, &o->pos, &o->vel);
    p.x = o->prev[0];
    p.y = o->prev[1];
    p.z = o->prev[2];
    p.w = 1.0f;
    VecSub_13be40(&d, &p, &o->pos);
    VecNormalize_13bd90(&d, &d);
    VecScale_13be00(&d, &d, 5.0f);
    VecAdd_13be20(&d, &p, &d);
    if (CollSegmentVsPlanesMaybe_364520(a, b, &d, o, &hp, &n, &t) != 0) {
        VecNormalize_13bd90(&n, &n);
        VecScale_13be00(&v80, &n, D_0047D244 + t);
        VecAdd_13be20(&hp, &hp, &v80);
        o->pos = hp;
        VecScale_13be00(&r, &o->vel, -1.0f);
        VecScale_13be00(&r, &n, 2.0f * Vu0InnerProduct_13bd60(&r, &n));
        VecAdd_13be20(&o->vel, &o->vel, &r);
        VecScale_13be00(&o->vel, &o->vel, D_0047D2A4);
        o->hit = 1;
        o->nrm[0] = n.x;
        o->nrm[1] = n.y;
        o->nrm[2] = n.z;
    } else {
        o->hit = 0;
    }
    o->prev[0] = old.x;
    o->prev[1] = old.y;
    o->prev[2] = old.z;
}
