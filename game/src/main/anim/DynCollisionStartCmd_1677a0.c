/* rgp:protos */
#define RGP_SELF_DynCollisionStartCmd_1677a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xEC];
    s32 unkEC;
    s32 *unkF0;
} Obj001677A0;

/*rgp*/
/*rgp*/

extern Obj001677A0 *D_00481154;
extern s32 D_00481158;
extern s32 D_00481180;

s32 DynCollisionStartCmd_1677a0(void *rgp_a0) {
    s32 temp_2;
    s32 temp_3;
    s32 var_4;
    u32 temp_5;
    u32 var_5;
    Obj001677A0 *temp_16;
    s32 base158;

    temp_2 = VariantGetInt_15f780((void *)rgp_a0);
    base158 = D_00481158;
    temp_5 = temp_2 * 4;
    temp_16 = D_00481154;
    temp_16->unkEC = temp_2;
    if (temp_5 & 0xF) {
        var_5 = (temp_5 >> 4) + 1;
    } else {
        var_5 = temp_5 >> 4;
    }
    temp_16->unkF0 = (s32 *)MemStackAllocQw_14d950(base158, var_5);
    var_4 = 0;
    while (var_4 < temp_16->unkEC) {
        temp_3 = var_4 * 4;
        var_4 += 1;
        *(s32 *)((u8 *)temp_16->unkF0 + temp_3) = 0;
    }
    D_00481180 = 0;
    return 1;
}
