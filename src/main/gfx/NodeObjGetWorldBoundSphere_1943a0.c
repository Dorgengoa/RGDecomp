#include "types.h"

typedef unsigned __int128 u128;
typedef struct { f32 m[16]; } M_001943a0;
typedef struct { f32 x, y, z, w; } V_001943a0;
typedef struct { u8 pad[0xA8]; s32 fA8; u8 pad2[0x24]; s32 fD0; u8 pad3[8]; f32 fDC; } T_001943a0;
typedef struct { f32 f0, f4, f8, fC; } O_001943a0;

extern void NodeCalcWorldMatrix_186130(T_001943a0 *, M_001943a0 *);
extern void MtxMulVec4_13c900(O_001943a0 *, M_001943a0 *, V_001943a0 *);

s32 NodeObjGetWorldBoundSphere_1943a0(T_001943a0 *p, O_001943a0 *out)
{
    M_001943a0 a;
    V_001943a0 b;
    f32 t;

    if (p->fA8 == 0) return 0;
    NodeCalcWorldMatrix_186130(p, &a);
    *(u128 *)&b = *(u128 *)((s32)p + 0xD0);
    t = p->fDC;
    b.w = 1.0f;
    MtxMulVec4_13c900(out, &a, &b);
    out->fC = t;
    return p->fA8;
}
