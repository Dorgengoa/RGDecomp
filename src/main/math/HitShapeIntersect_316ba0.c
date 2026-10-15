#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Shape {
    u8 type;        /* 00 */
    u8 pad1[3];
    s32 i4;         /* 04 */
    s32 i8;         /* 08 */
    u8 padC[4];
    Vec p;          /* 10 (.y 14, .w 1C) */
    Vec q;          /* 20 */
} Shape;
typedef struct Res { Vec v; f32 f10; s32 i14; s32 i18; } Res;

extern f32 sqrtf(f32);
void ClosestPointsSegSeg_1c93e0(Vec *, Vec *, Vec *, Vec *, Vec *, Vec *);
void ClosestPointOnSegment_1c9f60(Vec *, Vec *, Vec *, Vec *);
f32 VecDistSqXZ_1cb390(Vec *, Vec *);
f32 VecDistSq_1cb3c0(Vec *, Vec *);
f32 VecLengthSq_1cb470(Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
f32 VecDot3_1cba90(Vec *, Vec *);
void VecScale_1cbca0(Vec *, Vec *, f32);
void VecSubXyzW0_1cbce0(Vec *, Vec *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecAddXyzW1_1cbd80(Res *, Vec *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
void VecCopy_1cbe30(Vec *, Vec *);

s32 HitShapeIntersect_316ba0(Res *res, Shape *a, Shape *b) {
    Vec p90;
    Vec p80;
    Vec d70;
    Vec d60;
    Vec d50;
    f32 r;
    f32 len;
    f32 len2;
    f32 dot;
    f32 disc;
    f32 t;
    f32 d;

    if (res == 0 || a == 0 || b == 0) return 0;
    switch (a->type) {
    case 1:
        switch (b->type) {
        case 1:
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            if (!(VecDistSq_1cb3c0(&a->p, &b->p) <= r)) return 0;
            {
                res->f10 = 0.0f;
                VecCopy_1cbe30(&p90, &a->p);
                VecCopy_1cbe30(&p80, &b->p);
                goto tail;
            }
        case 2:
            ClosestPointOnSegment_1c9f60(&p80, &b->p, &b->q, &a->p);
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            if (!(VecDistSq_1cb3c0(&a->p, &p80) <= r)) return 0;
            {
                res->f10 = 0.0f;
                VecCopy_1cbe30(&p90, &a->p);
                p80.w = b->p.w;
                goto tail;
            }
        case 3:
            ClosestPointOnSegment_1c9f60(&p80, &b->p, &b->q, &a->p);
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            if (!(VecDistSq_1cb3c0(&a->p, &p80) <= r)) return 0;
            {
                res->f10 = 0.0f;
                VecCopy_1cbe30(&p90, &a->p);
                p80.w = b->p.w;
                goto tail;
            }
        default:
            return 0;
        }
        break;
    case 2:
        switch (b->type) {
        case 1:
            ClosestPointOnSegment_1c9f60(&p90, &a->p, &a->q, &b->p);
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            if (!(VecDistSq_1cb3c0(&p90, &b->p) <= r)) return 0;
            {
                res->f10 = 0.0f;
                VecCopy_1cbe30(&p80, &b->p);
                p90.w = a->p.w;
                goto tail;
            }
        case 2:
            ClosestPointsSegSeg_1c93e0(&p90, &p80, &a->p, &a->q, &b->p, &b->q);
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            if (!(VecDistSq_1cb3c0(&p90, &p80) <= r)) return 0;
            {
                res->f10 = 0.0f;
                p90.w = a->p.w;
                p80.w = b->p.w;
                goto tail;
            }
        case 3:
            ClosestPointsSegSeg_1c93e0(&p90, &p80, &a->p, &a->q, &b->p, &b->q);
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            if (!(VecDistSq_1cb3c0(&p90, &p80) <= r)) return 0;
            {
                res->f10 = 0.0f;
                p90.w = a->p.w;
                p80.w = b->p.w;
                goto tail;
            }
        default:
            return 0;
        }
        break;
    case 3:
        switch (b->type) {
        case 1:
            VecSub_1cbd00(&d70, &a->p, &b->p);
            t = b->p.w;
            r = a->p.w + t;
            r = r * r;
            len = VecLengthSq_1cb470(&d70);
            if (len <= r) {
                res->f10 = 0.0f;
                VecCopy_1cbe30(&p90, &a->p);
                VecCopy_1cbe30(&p80, &b->p);
                goto tail;
            }
            VecSub_1cbd00(&d60, &a->q, &a->p);
            len2 = VecLengthSq_1cb470(&d60);
            if (len2 <= 0.0f) return 0;
            dot = VecDot3_1cba90(&d60, &d70);
            disc = dot * dot - len2 * (len - r);
            if (disc < 0.0f) return 0;
            t = -(dot + sqrtf(disc)) / len2;
            res->f10 = t;
            if (t < 0.0f || 1.0f < t) return 0;
            VecScale_1cbca0(&d60, &d60, t);
            VecAdd_1cbdc0(&p90, &a->p, &d60);
            p90.w = a->p.w;
            VecCopy_1cbe30(&p80, &b->p);
            goto tail;
        case 2:
            return 0;
        case 3:
            return 0;
        default:
            return 0;
        }
        break;
    case 4:
        switch (b->type) {
        case 1:
            if (a->p.y < b->p.y - b->p.w) return 0;
            VecCopy_1cbe30(&p90, &a->p);
            VecCopy_1cbe30(&p80, &b->p);
            if (p90.y < p80.y) {
                d = p80.y - p90.y;
                p80.w = p80.w * p80.w - d * d;
                if (p80.w < 0.0f) p80.w = 0.0f;
                p80.w = sqrtf(p80.w);
                p80.y = p90.y;
            }
            t = p80.w;
            r = p90.w + t;
            r = r * r;
            if (!(VecDistSqXZ_1cb390(&p90, &p80) <= r)) return 0;
            {
                res->f10 = 0.0f;
                p90.y = p80.y;
                goto tail;
            }
        case 2:
            return 0;
        case 3:
            return 0;
        default:
            return 0;
        }
        break;
    default:
        return 0;
    }
tail:
    VecSubXyzW0_1cbce0(&d50, &p90, &p80);
    VecScaleToLength_1cb510(&d50, &d50, p80.w);
    VecAddXyzW1_1cbd80(res, &p80, &d50);
    res->i14 = b->i4;
    res->i18 = b->i8;
    return 1;
}
