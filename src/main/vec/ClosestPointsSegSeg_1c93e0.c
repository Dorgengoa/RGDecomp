#include "types.h"
#include "vec.h"

void VecSub_1cbd00(Vec4 *d, const Vec4 *a, const Vec4 *b);
f32 VecLengthSq_1cb470(const Vec4 *a);
f32 VecDistSq_1cb3c0(const Vec4 *a, const Vec4 *b);
f32 VecDotDiff_1cba40(const Vec4 *a, const Vec4 *b, const Vec4 *c);
f32 VecDot3_1cba90(const Vec4 *a, const Vec4 *b);
void VecLerpPoint_1cbac0(Vec4 *d, const Vec4 *a, const Vec4 *b, f32 t);
void VecCopy_1cbe30(Vec4 *d, const Vec4 *a);

static inline f32 ProjT(const Vec4 *e, const Vec4 *d)
{
    f32 den = VecDistSq_1cb3c0(e, d);
    if (den == 0.0f) return 0.0f;
    return VecDotDiff_1cba40(e, d, e) / den;
}

static inline f32 ClampA(f32 t)
{
    if (t <= 0.0f) return 0.0f;
    return (t >= 1.0f) ? 1.0f : t;
}

static inline f32 ClampB(f32 t)
{
    if (t < 0.0f) return 0.0f;
    return (t > 1.0f) ? 1.0f : t;
}

static inline void ClosestPtSeg(Vec4 *out, const Vec4 *pt, const Vec4 *a, const Vec4 *b)
{
    Vec4 e, d;
    f32 den, t;
    VecSub_1cbd00(&e, a, pt);
    VecSub_1cbd00(&d, b, pt);
    den = VecDistSq_1cb3c0(&e, &d);
    if (den == 0.0f) {
        t = 0.0f;
    } else {
        t = VecDotDiff_1cba40(&e, &d, &e) / den;
    }
    VecLerpPoint_1cbac0(out, b, a, ClampA(t));
}

void ClosestPointsSegSeg_1c93e0(Vec4 *out0, Vec4 *out1, const Vec4 *p0, const Vec4 *p1, const Vec4 *q0, const Vec4 *q1)
{
    Vec4 d1, d2, r;
    f32 a, e, b, denom, c, f, s, t;

    VecSub_1cbd00(&d1, p1, p0);
    a = VecLengthSq_1cb470(&d1);
    if (a == 0.0f) {
        ClosestPtSeg(out1, p0, q0, q1);
        VecCopy_1cbe30(out0, p0);
        return;
    }
    VecSub_1cbd00(&d2, q1, q0);
    e = VecLengthSq_1cb470(&d2);
    if (e == 0.0f) {
        ClosestPtSeg(out0, q0, p0, p1);
        VecCopy_1cbe30(out1, q0);
        return;
    }
    b = VecDot3_1cba90(&d1, &d2);
    denom = a * e - b * b;
    if (denom == 0.0f) {
        Vec4 e1, d1b, e2, d2b;
        f32 t1, t2;
        VecSub_1cbd00(&e1, p0, q0);
        VecSub_1cbd00(&d1b, p1, q0);
        t1 = ProjT(&e1, &d1b);
        VecSub_1cbd00(&e2, p0, q1);
        VecSub_1cbd00(&d2b, p1, q1);
        t2 = ProjT(&e2, &d2b);
        VecLerpPoint_1cbac0(out0, p1, p0, 0.5f * (ClampB(t1) + ClampB(t2)));
        ClosestPtSeg(out1, out0, q0, q1);
        return;
    }
    VecSub_1cbd00(&r, p0, q0);
    if (b == 0.0f) {
        s = -VecDot3_1cba90(&d1, &r) / a;
        t = VecDot3_1cba90(&d2, &r) / e;
        VecLerpPoint_1cbac0(out0, p1, p0, ClampB(s));
        VecLerpPoint_1cbac0(out1, q1, q0, ClampB(t));
        return;
    }
    VecLengthSq_1cb470(&r);
    c = VecDot3_1cba90(&d1, &r);
    f = VecDot3_1cba90(&d2, &r);
    s = (b * f - e * c) / denom;
    t = (a * f - b * c) / denom;
    if (0.0f <= s && s <= 1.0f) {
        if (!(0.0f <= t && t <= 1.0f)) {
            f32 tt = (t < 0.0f) ? 0.0f : 1.0f;
            f32 u = (tt * b - c) / a;
            t = tt;
            s = ClampB(u);
        }
    } else if (0.0f <= t && t <= 1.0f) {
        f32 ss = (s < 0.0f) ? 0.0f : 1.0f;
        f32 u = (c + ss * a) / b;
        s = ss;
        t = ClampB(u);
    } else {
        s = (s < 0.0f) ? 0.0f : 1.0f;
        t = (t < 0.0f) ? 0.0f : 1.0f;
    }
    VecLerpPoint_1cbac0(out0, p1, p0, s);
    VecLerpPoint_1cbac0(out1, q1, q0, t);
}
