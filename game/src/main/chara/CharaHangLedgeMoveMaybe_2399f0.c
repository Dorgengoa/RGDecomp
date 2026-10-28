/* rgp:protos */
#define RGP_SELF_CharaHangLedgeMoveMaybe_2399f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct Obj {
    V4 v[7];
    f32 px;
    f32 py;
    f32 pz;
    u32 flags;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];
extern f32 D_0047DB18;
extern f32 D_0047DB24;
extern f32 D_0047E730;
extern f32 D_0047E734;
extern f32 D_0047E738;
extern f32 D_0047E73C;
extern f32 D_0047E740;
extern f32 D_0047E744;
extern f32 D_0047E748;
extern f32 D_0047E74C;

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

void CharaHangLedgeMoveMaybe_2399f0(Obj *o, u8 *x, s32 id, s32 id2, s32 m, f32 r, V4 *out1, V4 *out2, V4 *w, f32 rr, f32 d)
{
    f32 hit;
    V4 pts[4] __attribute__((aligned(16)));
    f32 ang[4] __attribute__((aligned(16)));
    V4 q __attribute__((aligned(16)));
    u8 fb;
    s32 lo;
    s32 hi;
    s32 cnt;
    s32 k;
    s32 i;
    s32 go;
    f32 t;
    f32 best;
    f32 len;
    V4 *pa;
    V4 *pb;

    o->px = w->x;
    o->py = w->y;
    o->pz = w->z;
    if ((((o->flags & 0x80000000) != 0) ^ 1) == 0) {
        out2->x = o->px;
        out2->y = o->py;
        out2->z = o->pz;
        out2->w = 1.0f;
        out1->x = 0.0f;
        out1->y = 0.0f;
        out1->z = 0.0f;
        out1->w = 0.0f;
        return;
    }
    if (!(o->flags & 0x40000000) && !(o->flags & 0x20000000)) {
        best = 2.0f * rr;
        if (VecDistSqXZ_1cb390(o, &o->v[1]) <= best * best) {
            out1->x = 0.0f;
            out1->y = Atan2f_1291a8(o->v[4].x, o->v[4].z);
            out1->z = 0.0f;
            out1->w = 0.0f;
            VecLerpPoint_1cbac0(out2, o, &o->v[1], 0.5f);
            return;
        }
    }
    cnt = 0;
    if (d != 0.0f) {
        *(u128 *)&q = *(u128 *)(x + 0x180);
        {
        V4 dir __attribute__((aligned(16))) = {0};
        dir.x = d * o->v[4].z;
        dir.z = -(f32)d * o->v[4].x;
        {
        V4 tri[3] __attribute__((aligned(16))) = {0};
        V4 ray __attribute__((aligned(16)));
        V4 tmp __attribute__((aligned(16)));
        tri[0].y = D_0047DB18 * D_0045B080[0];
        tri[1].y = 0.0f;
        tri[2].y = D_0047DB24 * D_0045B080[0];
        VecScaleToLength_1cb510(&dir, &dir, r + ((d < 0.0f) ? -d : d));
        {
            f32 *p = (f32 *)&ray;
            p[0] = D_0047E730;
            p[1] = D_0047E734;
            p[2] = D_0047E738;
            p[3] = D_0047E73C;
        }
        ray.x = q.x;
        ray.y = o->py;
        ray.z = q.z;
        best = 1.0f;
        m &= ~2;
        for (i = 0; i < 3; i++) {
            VecAdd_1cbdc0(&tmp, &ray, &tri[i]);
            if (CollRaycastNearest_1c86e0(id, id2, m, &tmp, &dir, &hit) >= 0) {
                if (hit < best) {
                    best = hit;
                }
            }
        }
        if (best < 1.0f) {
            if (d < 0.0f) {
                d = -(best * (r - d) - r);
            } else {
                d = best * (r + d) - r;
            }
        }
        }
        }
    }
    k = 1;
    if (d < 0.0f) {
        hi = k;
        lo = 0;
        k = 2;
        go = (o->flags & 0x40000000) != 0;
        fb = (o->flags & 0x20000000) != 0;
    } else {
        lo = k;
        hi = 0;
        go = (o->flags & 0x20000000) != 0;
        fb = (o->flags & 0x40000000) != 0;
    }
    if (go) {
        ang[0] = Atan2f_1291a8(o->v[4 + k].x, o->v[4 + k].z);
        VecLerp_1cbb20(&pts[0], &o->v[4 - k], &o->v[lo], rr / VecDistXZ_1cb3f0(&o->v[lo], &o->v[4 - k]));
        cnt++;
    }
    ang[cnt] = Atan2f_1291a8(o->v[4].x, o->v[4].z);
    VecLerp_1cbb20(&pts[cnt], &o->v[hi], &o->v[lo], rr / VecDistXZ_1cb3f0(&o->v[lo], &o->v[hi]));
    ang[(s32)(u32)(cnt + 1)] = Atan2f_1291a8(o->v[4].x, o->v[4].z);
    VecLerp_1cbb20(&pts[cnt + 1], &o->v[lo], &o->v[hi], rr / VecDistXZ_1cb3f0(&o->v[hi], &o->v[lo]));
    cnt += 2;
    if (fb) {
        ang[cnt] = Atan2f_1291a8(o->v[4 + k].x, o->v[4 + k].z);
        VecLerp_1cbb20(&pts[cnt], &o->v[k + 1], &o->v[(s32)(u32)hi], rr / VecDistXZ_1cb3f0(&o->v[(s32)(u32)hi], &o->v[k + 1]));
        cnt++;
    }
    {
    V4 c __attribute__((aligned(16)));
    {
        f32 *p = (f32 *)&c;
        p[0] = D_0047E740;
        p[1] = D_0047E744;
        p[2] = D_0047E748;
        p[3] = D_0047E74C;
    }
    c.x = o->px;
    c.y = o->py;
    c.z = o->pz;
    i = 0;
    t = SegmentProjectTXZ_1ca2a0(&c, &pts[0], &pts[1]);
    goto check;
    do {
        i++;
        t = SegmentProjectTXZ_1ca2a0(&c, &pts[i], &pts[i + 1]);
    check:
        go = t >= 1.0f;
        if ((go ^ 1) != 0) {
            break;
        }
    } while (i + 2 < cnt);
out:
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (!(t <= 1.0f)) {
        t = 1.0f;
    }
    pa = &pts[i + 1];
    VecLerp_1cbb20(&c, pa, &pts[i], t);
    d = (d < 0.0f) ? -d : d;
    len = VecDist_1cb420(&c, pa);
    if (i + 2 == cnt && !(d <= len)) {
        d = len;
    }
    if (d <= len) {
        if (len == 0.0f) {
            VecCopy_1cbe30(&c, pa);
        } else {
            VecLerp_1cbb20(&c, pa, &c, d / len);
        }
    } else {
        i++;
        t = (d - len) / VecDist_1cb420(&pts[i], &pts[i + 1]);
        if (!(t <= 1.0f)) {
            t = 1.0f;
        }
        VecLerp_1cbb20(&c, &pts[i + 1], &pts[i], t);
    }
    out1->x = 0.0f;
    best = *(f32 *)((u32)&ang[i]);
    out1->y = AngleWrap_1cbf30(best + t * AngleWrap_1cbf30(ang[i + 1] - best));
    out1->z = 0.0f;
    out1->w = 0.0f;
    o->px = c.x;
    o->py = c.y;
    o->pz = c.z;
    VecCopyAsPoint_1cbe10(out2, &c);
    }
}
