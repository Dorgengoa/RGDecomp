/* rgp:protos */
#define RGP_SELF_CollMoveCharacterMaybe_16e530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;
typedef struct { s32 v[12]; } M12;
typedef struct { f32 v[4]; } F4;
typedef struct { s16 v[10]; } T10;
typedef struct {
    M12 m;
    F4 n;
    T10 ids;
    s32 f54;
    s32 f58;
    s32 f5C;
} Tri;

typedef struct Hit {
    M12 m;
    F4 n;
    T10 ids;
    s32 f54;
} Hit;

typedef struct Coll {
    f32 r;
    f32 h;
    f32 g;
    f32 step;
    f32 lift;
    f32 f14;
    f32 slope;
    s32 onGround;
    Hit h20;
    u8 pad78[8];
    s32 w80;
    u8 pad84[0xC];
    Hit h90;
    u8 padE8[8];
    Vec4 vF0;
    s32 w100;
} Coll;

extern f32 D_0047D1DC;
extern f32 D_0047D24C;
extern f32 D_0047D34C __attribute__((section(".sdata")));
extern f32 D_0047D440;

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

s32 CollMoveCharacterMaybe_16e530(Vec4 *pos, Vec4 *vel, Vec4 *out, Coll *c, Tri *tris, s32 n, s32 mask)
{
    Vec4 res __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    s32 idx[64] __attribute__((aligned(16)));
    Vec4 hits[64] __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    Vec4 tmp __attribute__((aligned(16)));
    Hit hit __attribute__((aligned(16)));
    Vec4 probe __attribute__((aligned(16)));
    Vec4 q __attribute__((aligned(16)));
    f32 r;
    f32 h;
    f32 g;
    f32 step;
    f32 f14;
    f32 slope;
    f32 lift;
    f32 l;
    f32 m;
    f32 lim;
    s32 k;

    r = c->r;
    if (r <= 0.0f) {
        r = 15.0f;
    }
    h = c->h;
    if (h <= 0.0f) {
        h = 4.0f;
    }
    g = c->g;
    step = c->step;
    f14 = c->f14;
    slope = c->slope;
    lift = c->lift;
    if (g <= 0.0f) {
        g = 34.0f;
    }
    if (step <= 0.0f) {
        step = 10.0f;
    }
    if (f14 <= 0.0f) {
        f14 = 4.0f;
    }
    if (slope <= 0.0f) {
        slope = 0.5f;
    }
    if (lift <= 0.0f) {
        lift = 0.5f * step;
    }
    out->x = pos->x;
    out->y = pos->y;
    out->z = pos->z;
    VecNormalize_13bd90(&dir, vel);
    VecScale_13be00(&dir, &dir, D_0047D440 * r);
    a.x = pos->x;
    a.y = pos->y + lift;
    a.z = pos->z;
    b.x = a.x + vel->x + 2.0f * dir.x;
    b.y = a.y;
    b.z = a.z + vel->z + 2.0f * dir.y;
    a.w = h;
    if (CollSweepSphereTrisMaybe_16ebe0(tris, n, &a, &b, 0x40, idx, hits, 1, mask) > 0) {
        *(u128 *)&v = *(u128 *)vel;
        v.y = 0.0f;
        l = VecLength_13d4a0(&v);
        m = 0.5f * r;
        lim = l;
        if (!(l <= m)) {
            lim = m;
        }
        sceVu0Normalize(&v, &v);
        sceVu0ScaleVector(&v, &v, lim);
        vel->x = v.x;
        vel->z = v.z;
    }
    a.x = pos->x;
    a.y = pos->y + step;
    a.z = pos->z;
    b.x = a.x + vel->x;
    b.y = a.y + vel->y;
    b.z = a.z + vel->z;
    a.w = h;
    VecAdd_13be20(&tmp, &b, &dir);
    for (k = 0; k < 2; k++) {
        if (CollSweepSphereTrisMaybe_16ebe0(tris, n, &a, &b, 0x40, idx, hits, 1, mask) <= 0) {
            a.x = b.x;
            b.x = a.x;
            a.y = b.y;
            a.z = b.z;
            b.z = a.z;
            b.y = a.y - step;
            break;
        }
        vel->x *= 0.5f;
        vel->z *= 0.5f;
        b.x = a.x + vel->x;
        b.y = a.y + vel->y;
        b.z = a.z + vel->z;
    }
    c->w80 = 0;
    c->onGround = 0;
    if (!(vel->y <= D_0047D34C)) {
        f14 = 0.0f;
    }
    *(u128 *)&probe = *(u128 *)&a;
    for (k = 0; k <= 0;) {
        if (CollMoveProbeGroundMaybe_16e2c0(&probe, &hit, &res, tris, n, mask, 2.0f * step, h)) {
            VecNormalize_13bd90(&hit.n, &hit.n);
            c->h20.m = hit.m;
            c->h20.n = hit.n;
            c->h20.ids = hit.ids;
            c->h20.f54 = hit.f54;
            c->h90.m = hit.m;
            c->h90.n = hit.n;
            c->h90.ids = hit.ids;
            c->h90.f54 = hit.f54;
            c->w80 = 1;
            c->onGround = 0;
            *(u128 *)&c->vF0 = *(u128 *)&res;
            if (!(res.y <= a.y + vel->y - step - f14)) {
                c->onGround = 1;
                if (hit.n.v[1] < slope) {
                    if (!(hit.n.v[1] > -slope)) {
                        k = 0;
                    }
                }
            }
            break;
        }
        k++;
        probe.x += D_0047D1DC;
        probe.z += D_0047D24C;
    }
    if (c->onGround != 0) {
        out->x = res.x;
        out->y = res.y;
        out->z = res.z;
    } else {
        out->x = b.x;
        out->y = b.y;
        out->z = b.z;
    }
    *(u128 *)&q = *(u128 *)out;
    q.y += lift;
    c->w100 = CollPushOutWallsMaybe_16d730(tris, n, &q, &b, mask, r, slope);
    if (c->w100 != 0) {
        q.x = b.x;
        q.z = b.z;
    }
    c->w100 = CollSpherePushOutMaybe_16dea0(tris, n, &q, &b, mask, r);
    if (c->w100 != 0) {
        out->x = b.x;
        out->z = b.z;
    }
    CollMoveEndMaybe_16e2b0(c);
    return 0;
}
