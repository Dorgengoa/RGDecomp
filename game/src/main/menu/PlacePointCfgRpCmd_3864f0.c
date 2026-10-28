/* rgp:protos */
#define RGP_SELF_PlacePointCfgRpCmd_3864f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00483404;
extern s32 D_00483408;
extern s32 D_0048340C;

s32 PlacePointCfgRpCmd_3864f0(s64 *arg0, s32 arg1)
{
    u8 sp40[0x20] __attribute__((aligned(16)));
    s32 var_17;
    void *temp_2;

    PlacePointInit_3869f0(sp40);
    PlacePointInit_3869f0(sp40);
    var_17 = 0;
    VariantReadVec3_15f6c0(sp40, (s32)arg0);
    arg0 += 3;
    VecAddInPlace_13e070(sp40, D_00483408);
    *(f32 *)(sp40 + 0xC) = 1.0f;
    if (arg1 > 3) {
        *(s32 *)(sp40 + 0x10) = VariantGetInt_15f780((s32)arg0++);
    }
    if (arg1 > 4) {
        var_17 = SlotGetInt_15f720((s32)arg0);
    }
    temp_2 = PlacePointListAppend_3865f0(D_00483404, sp40);
    if ((temp_2 != NULL) && (var_17 != 0)) {
        *(s32 *)((u8 *)temp_2 + 0x14) = ((s32)MemStackStrDup_14cff0(var_17, D_0048340C));
    }
    return 1;
}
