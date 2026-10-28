/* rgp:protos */
#define RGP_SELF_EventVolumeRecDebugDraw_2e49b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];

void EventVolumeRecDebugDraw_2e49b0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 m[16] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    s32 p;
    s32 i;

    if (*(s32 *)(arg0 + 0x10) == 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0x14) > 0) {
    } else {
        return;
    }
    EventVolumeRecGetPoint_2e4d40(arg0, v);
    MatFromPosScale_1cb2b0(m, v, 0.5f * D_0045B080[0]);
    MatMul_1cb700(m, arg2, m);
    DrawWireCube_1cc1b0(arg1, m, arg3);
    p = *(s32 *)(arg0 + 0x10);
    i = 0;
    while (i < *(s32 *)(arg0 + 0x14)) {
        EventVolumeDebugDraw_2e4f90(p, arg1, arg2, arg3);
        i++;
        p += 0x40;
    }
}
