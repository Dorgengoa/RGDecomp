#include "types.h"

typedef unsigned __int128 u128;
typedef struct { s32 f0, f4; f32 f8; f32 fC; } T_00387e50;
typedef struct { f32 m[16]; } M_00387e50;

extern void MtxRotY_13ce20(M_00387e50 *);
extern void MtxMulVec4_13c900(T_00387e50 *, M_00387e50 *, T_00387e50 *);

void VecFromYawLen_387e50(T_00387e50 *p, f32 unused, f32 v)
{
    M_00387e50 m;

    *(u128 *)p = 0;
    p->f8 = v;
    p->fC = 1.0f;
    MtxRotY_13ce20(&m);
    MtxMulVec4_13c900(p, &m, p);
}
