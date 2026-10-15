#define FDECLS f32 f23; f32 f22; f32 f21; f32 f20;
#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

extern "C" {
typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { f32 x, y, z, w; u8 pad[0x10]; } Hit;
typedef struct { u8 d[0x80]; } Ray;
typedef struct { u8 pad[0x46]; s16 flags; u8 pad48[0x18]; } Tri;

void VecCopy_1cbe30(Vec4 *, Vec4 *);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void CollSweepInit_1c81b0(Ray *, Vec4 *, Vec4 *, f32, f32);
s32 CollSweepCollectHits_1c7550(Ray *, Hit *, s32, Tri *, s32, s32);
extern u8 D_0045B080[0x400];
extern f32 D_0047DB14;

#define RT bool
RT CharaCollClampFloorCeilingMaybe_2364e0(void *self,
 Vec4 *out, Vec4 *in, Tri *tbl, s32 cnt, s32 flags, s32 dn, s32 up, f32 fa, f32 fb, f32 fc)
{
    Vec4 p;
    Hit hits[0x40];
    Vec4 a;
    Vec4 b;
    Ray m;
    Hit hits2[0x40];
    Vec4 c;
    Vec4 d;
    Ray m2;
    f32 hk;
    FDECLS
    f32 k;
    s32 si;
    s32 j;
    s32 n;
    s32 i;
    Hit *h;
    f32 thr;
    bool res;
    f32 t;
    f32 py;

    if (tbl == 0 || cnt <= 0) {
        VecCopy_1cbe30(out, in);
        return 0;
    }
    k = *(f32 *)D_0045B080;
    f20 = D_0047DB14 * k;
    f23 = 5.0f * f20;
    VecCopy_1cbe30(&p, in);
    si = -1;
    hk = 100.0f * k;
    py = p.y;
    f22 = py - hk;
    if (dn != 0) {
        VecCopy_1cbe30(&a, &p);
        VecCopy_1cbe30(&b, &p);
        {
        f32 dd = *(f32 *)D_0045B080;
        { f32 s_ = f23 + 2.0f * fa; f32 w_ = s_ + dd; a.y += w_; }
        { f32 s_ = f23 + fa; f32 w_ = s_ + dd; b.y -= w_; }
        }
        { Vec4 *q_ = &b; VecSub_1cbd00(q_, q_, &a); }
        CollSweepInit_1c81b0(&m, &a, &b, f23, 1.0f);
        n = CollSweepCollectHits_1c7550(&m, hits, 0x40, tbl, cnt, flags & ~0x1000);
        for (i = 0; i < n; i++) hits[i].y -= f23;
        py = p.y;
        for (h = hits, si = 0; si < n; si++, h++) {
            if (h->y <= py + fc) break;
        }
        if (si >= n) {
            si = -1;
        } else {
            f22 = hits[si].y;
        }
    }
    f21 = py + hk;
    j = -1;
    if (up != 0) {
        VecCopy_1cbe30(&c, &p);
        VecCopy_1cbe30(&d, &p);
        {
        f32 dd = *(f32 *)D_0045B080;
        { f32 s_ = f23 + fa; f32 w_ = s_ + dd; c.y -= w_; }
        { f32 s_ = f23 + 2.0f * fa; f32 w_ = s_ + dd; d.y += w_; }
        }
        { Vec4 *q_ = &d; VecSub_1cbd00(q_, q_, &c); }
        CollSweepInit_1c81b0(&m2, &c, &d, f23, 1.0f);
        n = CollSweepCollectHits_1c7550(&m2, hits2, 0x40, tbl, cnt, flags | 0x1800);
        for (i = 0; i < n; i++) hits2[i].y += f23;
        { f32 k3 = 3.0f; py = p.y; thr = (py > f22 ? py : f22) + k3 * (5.0f * f20); }
        for (h = hits2, j = 0; j < n; j++, h++) {
            if (!(h->y < thr)) break;
        }
        if (j >= n) {
            j = -1;
        } else {
            f21 = hits2[j].y;
        }
    }
    res = 0;
    if (f21 - f22 <= fa + 2.0f * f20) {
        if (((Tri *)((u8 *)tbl + si * sizeof(Tri)))->flags & 0x1000) {
            t = f21 - fa - f20;
            if (!(py <= t)) p.y = t;
        }
        res = 1;
    } else {
        if (j >= 0) {
            t = f21 - fa - f20;
            if (!(py <= t)) p.y = t;
            res = 1;
        }
        if (si >= 0) {
            {
                f32 u_ = f22 + fb;
                u_ += f20;
                if (p.y < u_) p.y = f22 + f20;
            }
        }
    }
    VecCopy_1cbe30(out, &p);
    return res;
}
}
