#include "types.h"

typedef struct { f32 v[3]; f32 pad; } FRow;
typedef struct { FRow r[5]; } FMat;
typedef struct { f32 v[15]; } FPack;

extern void SplineEvalBezierSolveTime_14b8a0(void *, FMat *, FMat *);

void SplineEvalBezierVec3_14b790(void *a, FPack *b, FPack *c)
{
    FMat m2;
    FMat m1;

    m2.r[0].v[0] = b->v[0];
    m2.r[0].v[1] = b->v[1];
    m2.r[0].v[2] = b->v[2];
    m2.r[1].v[0] = b->v[3];
    m2.r[1].v[1] = b->v[4];
    m2.r[1].v[2] = b->v[5];
    m2.r[2].v[0] = b->v[6];
    m2.r[2].v[1] = b->v[7];
    m2.r[2].v[2] = b->v[8];
    m2.r[3].v[0] = b->v[9];
    m2.r[3].v[1] = b->v[10];
    m2.r[3].v[2] = b->v[11];
    m2.r[4].v[0] = b->v[12];
    m2.r[4].v[1] = b->v[13];
    m2.r[4].v[2] = b->v[14];

    m1.r[0].v[0] = c->v[0];
    m1.r[0].v[1] = c->v[1];
    m1.r[0].v[2] = c->v[2];
    m1.r[1].v[0] = c->v[3];
    m1.r[1].v[1] = c->v[4];
    m1.r[1].v[2] = c->v[5];
    m1.r[2].v[0] = c->v[6];
    m1.r[2].v[1] = c->v[7];
    m1.r[2].v[2] = c->v[8];
    m1.r[3].v[0] = c->v[9];
    m1.r[3].v[1] = c->v[10];
    m1.r[3].v[2] = c->v[11];
    m1.r[4].v[0] = c->v[12];
    m1.r[4].v[1] = c->v[13];
    m1.r[4].v[2] = c->v[14];

    SplineEvalBezierSolveTime_14b8a0(a, &m2, &m1);
}
