/* rgp:protos */
#define RGP_SELF_CharaCollideWallsMaybe_236cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} __attribute__((aligned(16))) Vec4;

typedef struct Tri {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 n;
    u8 pad40[6];
    s16 flags;
    u8 pad48[0x18];
} Tri;

typedef struct Hit {
    Vec4 p;
    Vec4 n;
    f32 d;
    u8 pad24[0xC];
} Hit;

typedef struct Prm {
    u8 pad0[0x4C8];
    f32 x4C8;
    f32 x4CC;
} Prm;

typedef struct Ent {
    u8 pad0[0x3D0];
    u64 x3D0;
    u8 pad3D8[0x3F4 - 0x3D8];
    Prm *x3F4;
} Ent;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 sqrtf(f32);
extern f32 D_0045B080[];
extern f32 D_0047D1EC;
extern f32 D_0047D1FC;
extern f32 D_0047DA0C;
extern f32 D_0047DAB4;
extern f32 D_0047DAC0;
extern f32 D_0047DADC;
extern f32 D_0047DB14;
extern f32 D_0047DB44;

#define Clear(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

#pragma divbyzerocheck on
#pragma opt_arithtransformation off
void CharaCollideWallsMaybe_236cb0(Ent *e, Tri *tris, s32 n, Vec4 *up, Vec4 *pos, Vec4 *vel, f32 dy)
{
    Vec4 a750 __attribute__((aligned(16)));
    Vec4 a740 __attribute__((aligned(16)));
    Hit buf[32] __attribute__((aligned(16)));
    Vec4 d130 __attribute__((aligned(16)));
    Vec4 d120 __attribute__((aligned(16)));
    Vec4 s110 __attribute__((aligned(16)));
    Vec4 s100 __attribute__((aligned(16)));
    Vec4 acc __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    Vec4 t0d0 __attribute__((aligned(16)));
    Vec4 t0c0 __attribute__((aligned(16)));
    Prm *p;
    f32 sc;
    f32 m;
    f32 r;
    f32 h;
    f32 r2;
    f32 l;
    f32 f;
    Hit *out;
    s32 pass;
    Tri *t;
    s32 i;
    s32 cnt;
    s32 it;
    Hit *q;
    s32 k;
    f32 lim;
    f32 ang;
    f32 lo;
    f32 hi;
    f32 a;
    f32 best;
    f32 pr;
    f32 s;
    f32 v;

    p = e->x3F4;
    if (p == 0 || tris == 0 || n <= 0) {
        return;
    }
    sc = D_0045B080[0];
    m = D_0047DAC0 * sc;
    if (p != 0) {
        r = p->x4C8 * (D_0047DB14 * sc);
    } else {
        r = 0.0f;
    }
    r = r > m ? r : m;
    h = 0.0f;
    if (r <= h) {
        return;
    }
    m = D_0047DAB4 * sc;
    if (p != 0) {
        h = p->x4CC * (D_0047DB14 * sc);
    }
    h = h > m ? h : m;
    out = buf;
    if (!(e->x3D0 & 0x10000000000ULL)) {
        VecCopy_1cbe30(&a750, pos);
        VecCopy_1cbe30(&a740, pos);
        a750.y += dy;
        a740.y += 0.0f + h - D_0047DADC * sc;
        r2 = 1.25f * r;
        r2 = r2 * r2;
        for (pass = 0; pass < 2; pass++) {
            t = tris;
            for (i = 0; i < n; i++, t++) {
                if (!(out - buf < 32)) {
                    break;
                }
                if (pass == 0) {
                    if (t->flags & 0x800) {
                        continue;
                    }
                } else if (!(t->flags & 0x800)) {
                    continue;
                }
                if (!TriSlabClosestPointXZMaybe_23a850(out, t, &a750, a740.y - a750.y)) {
                    continue;
                }
                VecSub_1cbd00(&d130, out, pos);
                l = VecLengthSqXZ_1cb450(&d130, 0);
                if (l <= D_0047DB44) {
                    continue;
                }
                if (r2 <= l) {
                    continue;
                }
                out->n.x = d130.x;
                *(s32 *)&out->n.y = 0;
                out->n.z = d130.z;
                *(s32 *)&out->n.w = 0;
                VecNormalize_1cbb80(&out->n, &out->n);
                f = VecSubDotXZ_1cba10(out, up, &t->n);
                if (f * VecDot3_1cba90(&out->n, &t->n) < 0.0f) {
                    f = 2.0f * VecDot3_1cba90(&out->n, &t->n);
                    VecScale_1cbca0(&d120, &t->n, f / VecLengthSq_1cb470(&t->n, 0));
                    VecSub_1cbd00(&out->n, &out->n, &d120);
                }
                out->d = D_0047D1EC;
                out++;
            }
            if (out != buf) {
                break;
            }
        }
    }
    cnt = out - buf;
    if (cnt <= 0) {
        return;
    }
    lim = r * r;
    r2 = D_0047DA0C * (f32)D_0045B080[0];
    r2 = r + r2;
    r2 = r2 * r2;
    for (it = 0; it < 2; it++) {
        VecCopy_1cbe30(&s110, pos);
        VecCopy_1cbe30(&s100, vel);
        Clear(&acc, 0x10)
        k = 0;
        q = buf;
        for (i = 0; i < cnt; i++, q++) {
            if (q->d < lim) {
                q->d = D_0047D1EC;
                continue;
            }
            q->d = VecDistSqXZ_1cb390(pos, q);
            if (q->d < lim) {
                VecAdd_1cbdc0(&acc, &acc, &q->n);
                k++;
            }
        }
        if (k <= 0) {
            continue;
        }
        ang = Atan2f_1291a8(acc.x, acc.z);
        lo = 0.0f;
        hi = lo;
        q = buf;
        for (i = 0; i < cnt; i++, q++) {
            if (!(q->d < lim)) {
                continue;
            }
            a = AngleWrap_1cbf30(Atan2f_1291a8(q->n.x, q->n.z) - ang);
            if (!(lo <= a)) {
                lo = a;
            }
            if (hi < a) {
                hi = a;
            }
        }
        a = AngleWrap_1cbf30(D_0047D1FC + (0.0f + ang + 0.5f * (lo + hi)));
        Clear(&dir, 0x10)
        dir.x = Sinf_128fd0(a);
        dir.z = Cosf_128d30(a);
        q = buf;
        best = 0.0f;
        for (i = 0; i < cnt; i++, q++) {
            if (!(q->d < lim)) {
                continue;
            }
            VecSub_1cbd00(&t0d0, pos, q);
            pr = VecDotXZ_1cba70(&t0d0, &dir);
            s = pr * pr - (VecLengthSqXZ_1cb450(&t0d0, 0) - r2);
            if (s <= 0.0f) {
                continue;
            }
            s = sqrtf(s) - pr;
            if (s < best) {
                continue;
            }
            best = s;
        }
        if (best <= 0.0f) {
            continue;
        }
        VecScale_1cbca0(&acc, &dir, best);
        VecAdd_1cbdc0(pos, pos, &acc);
        v = VecDot3_1cba90(&dir, vel);
        if (v < 0.0f) {
            VecScale_1cbca0(&t0c0, &dir, v);
            VecSub_1cbd00(vel, vel, &t0c0);
        }
    }
    VecLerpPoint_1cbac0(pos, pos, &s110, 0.5f);
    VecLerpDir_1cbaf0(vel, vel, &s100, 0.5f);
}
