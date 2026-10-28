/* rgp:protos */
#define RGP_SELF_InvFreeCategory8Items_3c8d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

typedef struct Item003c8d70 {
    u8 pad0[6];
    s16 unk6;
    u8 pad8[2];
    u8 unkA;
} Item003c8d70;

typedef struct S003c8d70 {
    u8 pad0[0x168];
    s32 unk168;
} S003c8d70;

/*rgp*/
/*rgp*/
extern u8 D_00465B00[0x400];
extern u8 D_00465B08[0x400];
extern u8 D_00465B50[0x400];

s32 InvFreeCategory8Items_3c8d70(S003c8d70 *arg0) {
    s32 temp_3;
    s32 temp_16;
    s32 temp_17;
    s32 temp_18;
    s32 var_19;
    Item003c8d70 *temp_2;

    if (arg0->unk168 == 0) {
        return 0;
    }
    var_19 = 0;
    temp_18 = (*(s32 *)D_00465B00);
    temp_17 = (*(s32 *)D_00465B08);
    temp_16 = (*(s32 *)D_00465B50);
    while (var_19 < temp_16) {
        temp_2 = ((Item003c8d70 *)PoolGetUsedElem_36acb0(arg0->unk168, var_19));
        if ((temp_2 != NULL) && (((u64)((s64)temp_2->unkA << 0x3E) >> 0x3F) == 0)) {
            temp_3 = temp_2->unk6;
            if ((temp_3 >= temp_18) && (temp_3 <= temp_17)) {
                PoolFreeElem_36a8e0(arg0->unk168, var_19);
            }
        }
        var_19 += 1;
    }
    return 1;
}
