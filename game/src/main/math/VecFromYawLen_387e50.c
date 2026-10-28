/* rgp:protos */
#define RGP_SELF_VecFromYawLen_387e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct { s32 f0, f4; f32 f8; f32 fC; } T_00387e50;
typedef struct { f32 m[16]; } M_00387e50;

/*rgp*/
/*rgp*/

void VecFromYawLen_387e50(T_00387e50 *p, f32 unused, f32 v)
{
    M_00387e50 m __attribute__((aligned(16)));

    *(u128 *)p = 0;
    p->f8 = v;
    p->fC = 1.0f;
    MtxRotY_13ce20(&m, (float)unused);
    MtxMulVec4_13c900(p, &m, p);
}
