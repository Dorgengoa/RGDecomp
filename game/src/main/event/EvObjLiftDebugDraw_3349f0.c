/* rgp:protos */
#define RGP_SELF_EvObjLiftDebugDraw_3349f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
/*rgp*/
/*rgp*/
/*rgp*/
extern V4 D_0047F5F0 __attribute__((section(".sdata")));

void EvObjLiftDebugDraw_3349f0(u8 *arg0, s32 arg1) {
    u8 sp60[0x40] __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    u8 *p;
    s32 i;

    if ((*(s32 *)(arg0 + 0xD0) & 0x02000000) && *(s32 *)(arg0 + 0xEC) != 0) {
        XformGetMatrix_2e7750(arg0 + 0x10, sp60);
        *(V4 *)&v = D_0047F5F0;
        EventVolumeRecDebugDraw_2e49b0(*(s32 *)(arg0 + 0xEC), arg1, sp60, &v);
        p = *(u8 **)(arg0 + 0xE4);
        i = 0;
        while (i < *(s16 *)(arg0 + 0xEA)) {
            EvTargetSetDrawBox_3365a0(p, arg1);
            i++;
            p += 0x118;
        }
    }
}
