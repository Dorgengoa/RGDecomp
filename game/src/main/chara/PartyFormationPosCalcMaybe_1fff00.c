/* rgp:protos */
#define RGP_SELF_PartyFormationPosCalcMaybe_1fff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];
extern f32 D_0047D26C;

s32 PartyFormationPosCalcMaybe_1fff00(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3)
{
    f32 m[16] __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));

    if (SpotGetMatrixByIdMaybe_200050(m, arg2) == 0) {
        return 0;
    }
    if (PartyCountExcludingLeader_3c2610(*(s32 *)(((u8 *)GetGameData_1fede0()) + 0x18), 1, 1) == 2) {
        if (arg3 & 1) {
            v.y = 0.0f;
            v.x = -1.0f * D_0045B080[0];
            v.w = 1.0f;
            v.z = D_0047D26C * D_0045B080[0];
        } else {
            v.y = 0.0f;
            v.x = D_0045B080[0];
            v.w = 1.0f;
            v.z = D_0047D26C * D_0045B080[0];
        }
    } else {
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 2.0f * D_0045B080[0];
        v.w = 1.0f;
    }
    MatMulPoint_1cb8e0(arg0, m, &v);
    arg1[0] = 0.0f;
    arg1[1] = Atan2f_1291a8(m[12] - arg0[0], m[14] - arg0[2]);
    arg1[2] = 0.0f;
    arg1[3] = 0.0f;
    return 1;
}
