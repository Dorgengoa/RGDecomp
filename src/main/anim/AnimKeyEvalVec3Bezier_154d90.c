#include "types.h"
#include "vec.h"

typedef struct Key {
    f32 time;       /* 0x00 */
    s32 a;          /* 0x04 */
    s32 b;          /* 0x08 */
    s32 c;          /* 0x0C */
    s32 d;          /* 0x10 */
    s32 i0;         /* 0x14 */
    s32 i1;         /* 0x18 */
    s32 e;          /* 0x1C */
    s32 f;          /* 0x20 */
} Key;

typedef struct Frm {
    Vec4 pos;
    Vec4 a;
    Vec4 b;
    Vec4 c;
    Vec4 d;
} Frm;

typedef struct F15 {
    f32 v[15];
} F15;

typedef struct S15 {
    s16 v[15];
} S15;

typedef struct Track {
    u8 pad0;
    u8 kind;        /* 0x01 */
    u8 n2;          /* 0x02 */
    u8 pad3;
    s16 h4;         /* 0x04 */
    u16 h6;         /* 0x06 */
    s32 m8;         /* 0x08 */
    void *data;     /* 0x0C */
    f32 s10;        /* 0x10 */
    f32 s14;        /* 0x14 */
    f32 s18;        /* 0x18 */
    u8 pad1C[4];
    f32 s20;        /* 0x20 */
    f32 s24;        /* 0x24 */
    f32 s28;        /* 0x28 */
} Track;

extern void SplineEvalBezierVec3_14b790(f32 *, F15 *, F15 *, f32, f32, f32);
extern void SplineEvalBezierSolveTime_14b8a0(f32 *, Frm *, Frm *, f32, f32, f32);
extern f32 AnimKeyFindSpan_155ff0(Key *);

#define K (1.0f / 32768.0f)

void AnimKeyEvalVec3Bezier_154d90(f32 *out, Track *t, f32 time)
{
    Key k;
    Frm A;
    Frm B;
    f32 f;
    F15 *fr;
    S15 *p;
    S15 *q;

    k.a = t->n2;
    k.b = t->m8;
    k.d = t->h6;
    k.time = time;
    k.c = t->h4;
    f = AnimKeyFindSpan_155ff0(&k);
    if (t->kind == 0x20) {
        fr = (F15 *)t->data;
        if (f == 0.0f) {
            F15 *r = &fr[k.i0];
            out[0] = r->v[0];
            out[1] = r->v[1];
            out[2] = r->v[2];
            return;
        }
        SplineEvalBezierVec3_14b790(out, &fr[k.i0], &fr[k.i1], (f32)k.e, (f32)k.f, f);
    } else if (t->kind == 0x10) {
        p = &((S15 *)t->data)[k.i0];
        q = &((S15 *)t->data)[k.i1];
        if (f == 0.0f) {
            out[0] = K * (f32)p->v[0] * t->s10;
            out[1] = K * (f32)p->v[1] * t->s14;
            out[2] = K * (f32)p->v[2] * t->s18;
            return;
        }
        A.pos.x = K * (f32)p->v[0] * t->s10;
        A.pos.y = K * (f32)p->v[1] * t->s14;
        A.pos.z = K * (f32)p->v[2] * t->s18;
        A.a.x = K * (f32)p->v[3] * t->s20;
        A.a.y = K * (f32)p->v[4] * t->s24;
        A.a.z = K * (f32)p->v[5] * t->s28;
        A.b.x = K * (f32)p->v[6] * t->s20;
        A.b.y = K * (f32)p->v[7] * t->s24;
        A.b.z = K * (f32)p->v[8] * t->s28;
        B.pos.x = K * (f32)q->v[0] * t->s10;
        B.pos.y = K * (f32)q->v[1] * t->s14;
        B.pos.z = K * (f32)q->v[2] * t->s18;
        B.c.x = K * (f32)q->v[9] * t->s20;
        B.c.y = K * (f32)q->v[10] * t->s24;
        B.c.z = K * (f32)q->v[11] * t->s28;
        B.d.x = K * (f32)q->v[12] * t->s20;
        B.d.y = K * (f32)q->v[13] * t->s24;
        B.d.z = K * (f32)q->v[14] * t->s28;
        SplineEvalBezierSolveTime_14b8a0(out, &A, &B, (f32)k.e, (f32)k.f, f);
    }
}
