#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

extern f32 Atan2f_1291a8(f32, f32);
extern void MatMulPoint_1cb8e0(f32 *, f32 *, V4 *);
extern u8 *GetGameData_1fede0(void);
extern s32 SpotGetMatrixByIdMaybe_200050(f32 *, s32);
extern s32 PartyCountExcludingLeader_3c2610(s32, s32, s32);
extern f32 D_0045B080[];
extern f32 D_0047D26C;

s32 PartyFormationPosCalcMaybe_1fff00(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3)
{
    f32 m[16];
    V4 v;

    if (SpotGetMatrixByIdMaybe_200050(m, arg2) == 0) {
        return 0;
    }
    if (PartyCountExcludingLeader_3c2610(*(s32 *)(GetGameData_1fede0() + 0x18), 1, 1) == 2) {
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
