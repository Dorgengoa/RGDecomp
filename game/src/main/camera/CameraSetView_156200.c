/* rgp:protos */
#define RGP_SELF_CameraSetView_156200 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct { u128 r[4]; } M4;
typedef struct {
    u8 pad0[0xB0];
    M4 mB0;
    M4 mF0;
    M4 m130;
    u128 v170;
    M4 m180;
    M4 m1C0;
    u8 pad200[0x50];
    M4 m250;
    M4 m290;
    M4 m2D0;
} Obj;

/*rgp*/

void CameraSetView_156200(Obj *arg0, M4 *arg1, u128 *arg2) {
    M4 m __attribute__((aligned(16)));

    arg0->mB0.r[0] = arg1->r[0];
    arg0->mB0.r[1] = arg1->r[1];
    arg0->mB0.r[2] = arg1->r[2];
    arg0->mB0.r[3] = arg1->r[3];
    arg0->v170 = *arg2;
    MtxMul_13d240(&arg0->m180, &arg0->mF0, &arg0->mB0);
    MtxMul_13d240(&arg0->m1C0, &arg0->m130, &arg0->m180);
    MtxMul_13d240(&arg0->m290, &arg0->m250, &arg0->mB0);
    m.r[0] = arg0->m130.r[0];
    m.r[1] = arg0->m130.r[1];
    m.r[2] = arg0->m130.r[2];
    m.r[3] = arg0->m130.r[3];
    ((s32 *)&m.r[3])[0] = 0;
    ((s32 *)&m.r[3])[1] = 0;
    MtxMul_13d240(&arg0->m2D0, &m, &arg0->m180);
}
