/* rgp:protos */
#define RGP_SELF_MapModelCfgClothWind_195a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047E160;
extern f32 D_0047E164;
extern f32 D_0047E168;
extern f32 D_0047E16C;
extern void *D_00481354;

s32 MapModelCfgClothWind_195a20(s64 *arg0, s32 arg1) {
    f32 sp40[4] __attribute__((aligned(16)));
    f32 t20;
    f32 *qv;
    u8 *ctx;

    if (D_00481354 == 0) {
        return 0;
    }
    t20 = VariantGetFloat_15f740(arg0++);
    qv=sp40;
    qv[0] = D_0047E160;
    qv[1] = D_0047E164;
    qv[2] = D_0047E168;
    qv[3] = D_0047E16C;
    if (arg1 >= 4) {
        VariantReadVec3_15f6c0(qv, (s32)arg0);
    }
    ctx=(u8*)D_00481354;
    *(f32 *)(ctx+0x38)=t20;
    sceVu0Normalize(ctx+0x40,sp40);
    return 1;
}
