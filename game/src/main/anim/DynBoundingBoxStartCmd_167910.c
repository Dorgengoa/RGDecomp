/* rgp:protos */
#define RGP_SELF_DynBoundingBoxStartCmd_167910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void memset(void *, s32, s32);

typedef struct S_00167910 {
    u8 pad0[0xD4];
    s32 unkD4;
    u8 pad_D8[0xE4 - 0xD8];
    s32 unkE4;
    u8 *unkE8;
} S_00167910;

extern S_00167910 *D_00481154;
extern s32 D_00481158;

s32 DynBoundingBoxStartCmd_167910(void *rgp_a0)
{
    s32 temp_2;
    S_00167910 *temp_16;
    u32 temp_5;
    u32 var_5;
    s32 var_17;
    s32 temp_18;

    s32 temp_8;

    temp_2 = VariantGetInt_15f780((void *)rgp_a0);
    temp_8 = D_00481158;
    temp_16 = D_00481154;
    temp_5 = temp_2 * 0x30;
    temp_16->unkE4 = temp_2;
    if (temp_5 & 0xF) {
        var_5 = (temp_5 >> 4) + 1;
    } else {
        var_5 = temp_5 >> 4;
    }
    temp_16->unkE8 = (u8 *)MemStackAllocQw_14d950(temp_8, var_5);
    var_17 = 0;
    while (var_17 < temp_16->unkD4) {
        temp_18 = var_17 * 0x30;
        memset(temp_16->unkE8 + temp_18, 0, 0x30);
        var_17 += 1;
        *(s32 *)(temp_16->unkE8 + temp_18 + 0x20) = -1;
    }
    return 1;
}
