/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"
#pragma opt_pulloutconstants off
#include "vec.h"

struct Tri {
    Vec4 v[3];
    Vec4 n;
    s16 pad40[2];
    s16 type;
    s16 flags;
    u8 pad48[0x18];
};

struct Hit {
    Vec4 pt;
    s32 idx;
    u8 pad[0xC];
};

struct Box {
    u8 pad[0x80];
};

struct Prm {
    u8 pad[0x10];
    s32 f10;
};

class Cam {
public:
    u8 pad000[0x60];
    Vec4 v60;
    u8 pad070[0x50];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Prm * s48(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Prm *, (void *, int, int, int), 0x48, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad0C4[0x1C];
    Vec4 vE0;
    Vec4 vF0;
    u8 pad100[0x20];
    Vec4 v120;
    u8 pad130[0x100];
    Vec4 v230;
    s32 f240;
};

extern "C" {
s32 DoubleLess_1002b0(double, f64);
f64 dpmul(f64, f64);
double fptodp(f32);
void VecAddInPlace_13e070(Vec4 *, Vec4 *);
s32 CollSweepCollectHits_1c7550(Box *, Hit *, s32, Tri *, s32, s32);
void CollSweepInit_1c81b0(Box *, Vec4 *, Vec4 *, f32, f32);
f32 VecDist_1cb420(Vec4 *, Vec4 *);
f32 VecLength_1cb4c0(Vec4 *);
void VecNegate_1cb9a0(Vec4 *, Vec4 *);
f32 VecDotDiff_1cba40(void *, void *, Vec4 *);
f32 VecDot3_1cba90(Vec4 *, Vec4 *);
void VecLerpPoint_1cbac0(Vec4 *, Vec4 *, Vec4 *, f32);
void VecNormalize_1cbb80(Vec4 *, Vec4 *);
void VecDivScalar_1cbbf0(Vec4 *, Vec4 *, f32);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
extern f32 D_0045B080[0x100];
extern f64 D_0047D190;
extern f32 D_0047D288;
extern f32 D_0047D844;

s32 CameraSweepEyeCollisionMaybe_160c90(Cam *cam, Tri *tris, s32 count, int rgp_a3) {
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 e __attribute__((aligned(16)));
    Vec4 h __attribute__((aligned(16)));
    Vec4 g __attribute__((aligned(16)));
    Box box __attribute__((aligned(16)));
    Hit hit[64] __attribute__((aligned(16)));
    f32 len;
    s32 n;
    f32 unit;
    s32 k;
    s32 i;
    s32 nr;
    s32 fr;
    s32 mid;
    f32 lim;
    Tri *t;
    f32 f;

    s32 odd;
    s32 even;
    s32 cnt;
    s32 j;


    cam->s48((int)(long)(tris), (int)(long)(count), (int)(long)(rgp_a3));
    if (cam->f240 != 0) {
        a = cam->v230;
        VecAddInPlace_13e070(&a, &cam->v120);
    } else {
        a = cam->vE0;
    }
    b = cam->vF0;
    VecSub_1cbd00(&d, &b, &a);
    len = VecDist_1cb420(&b, &a);
    VecDivScalar_1cbbf0(&d, &d, len);
    VecCopy_1cbe30(&e, &a);
    VecScale_1cbca0(&g, &d, 2.0f);
    VecAdd_1cbdc0(&h, &b, &g);
    VecSub_1cbd00(&h, &h, &e);
    CollSweepInit_1c81b0(&box, &e, &h, 1.0f, 1.0f);
    n = CollSweepCollectHits_1c7550(&box, hit, 0x40, tris, count, 0);
    if (n > 0) {
        VecLength_1cb4c0(&h);
        unit = D_0045B080[0];
        k = -1;
        i = 0;
        nr = k;
        fr = k;
        mid = k;
        lim = 1.25f * unit;
        while (i < n) {
            t = &tris[hit[i].idx];
            if (VecDot3_1cba90(&d, &t->n) < 0.0f) VecNegate_1cb9a0(&t->n, &t->n);
            if (t->type == 2) {
                i++;
                continue;
            }
            if (t->type != 1) goto out;
            f = VecDotDiff_1cba40(t, &a, &t->n);
            k = i;
            if (f < lim) {
                nr = i;
                i++;
                continue;
            }
            if (VecDotDiff_1cba40(&cam->v60, t, &t->n) < D_0047D844 * unit) {
                fr = i;
            } else {
                mid = i;
            }
            for (i++; i < n; i++) {
                t = &tris[hit[i].idx];
                if (VecDot3_1cba90(&d, &t->n) < 0.0f) VecNegate_1cb9a0(&t->n, &t->n);
                if (t->type == 1) continue;
                if (t->type != 2) goto out;
            }
            break;
        }
    out:
        if (i < n) {
            if (k >= 0 && k != i) {
                { Tri *tk = &tris[hit[k].idx]; f = VecDotDiff_1cba40(&tris[hit[i].idx], tk, &tk->n); }
                f = f < 0.0f ? -f : f;
                if (((unsigned char)DoubleLess_1002b0(fptodp(f), dpmul(*(volatile f64 *)&D_0047D190, unit)))) {
                    i = k;
                    k = -1;
                    nr = k;
                    fr = k;
                    mid = k;
                }
            }
            if (mid < 0) VecCopy_1cbe30(&b, &hit[i].pt);
        }
        if (k >= 0) {
            if (mid >= 0) {
                VecLerpPoint_1cbac0(&b, &hit[mid].pt, &cam->vF0, 0.5f);
            } else if (nr >= 0) {
                VecLerpPoint_1cbac0(&b, &b, &cam->vF0, 0.5f);
            }
            if (fr < 0) {
                { f32 c = cam->vF0.y; f32 hf = 0.5f; b.y = c + hf * (a.y - c); }
                cam->s48()->f10 = 0;
            }
        }
        { s32 k2;
        odd = -1;
        even = odd;
        cnt = 0;
        for (j = 0; j < i; j++) {
            { Tri *tj = &tris[hit[j].idx]; if (tj->type != 2) continue; }
            cnt++;
            if (cnt & 1) {
                odd = j;
            } else {
                even = j;
            }
        }
        }
        if (cnt > 0) {
            if (cnt & 1) {
                VecCopy_1cbe30(&b, &hit[odd].pt);
            } else if (VecDist_1cb420(&b, &hit[even].pt) < D_0047D288 * unit) {
                VecCopy_1cbe30(&b, &hit[odd].pt);
            }
        }
        VecCopy_1cbe30(&cam->vF0, &b);
    }
    VecSub_1cbd00(&d, &cam->vF0, &a);
    VecNormalize_1cbb80(&d, &d);
    if (!(VecLength_1cb4c0(&d) <= len)) {
        VecScale_1cbca0(&g, &d, len);
        VecAdd_1cbdc0(&cam->vF0, &a, &g);
    }
    return n > 0;
}
}
