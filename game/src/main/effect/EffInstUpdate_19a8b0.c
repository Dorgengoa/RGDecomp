/* rgp:protos */
#define RGP_SELF_EffInstUpdate_19a8b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct Item0019a8b0 {
    void *unk0;
    u8 pad4[8];
    void *unkC;
} Item0019a8b0;

typedef struct S0019a8b0_Arg0 {
    u8 pad0[0x9C];
    s32 unk9C;
    Item0019a8b0 **unkA0;
} S0019a8b0_Arg0;

typedef struct S0019a8b0_Arg2 {
    u8 pad0[0xC4];
    s32 unkC4;
} S0019a8b0_Arg2;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

#pragma opt_propagation on
s32 EffInstUpdate_19a8b0(S0019a8b0_Arg0 *arg0, s32 arg1, S0019a8b0_Arg2 *arg2, f32 fparg0)
{
    void * arg_h1;
    s32 var_22;
    Item0019a8b0 **var_21;
    u8 *var_20;
    u8 spA0[0x50] __attribute__((aligned(16)));
    s32 var_19;
    Item0019a8b0 *temp_18;
    void *temp_4;
    

    var_22 = 0;
    EffObjStepChannels_1a9b50(arg0, arg2, fparg0);
    XformInitIdentity_1a86a0(spA0);
    arg_h1 = spA0;
    XformPairComposeWithParent_199d60(arg2, arg_h1);
    var_20 = (u8 *)arg2->unkC4;
    var_21 = arg0->unkA0;
    if (var_20 == NULL) {
        
        return 0;
    }
    var_19 = 0;
    while (var_19 < arg0->unk9C) {
        temp_18 = *var_21;
        temp_4 = temp_18->unkC;
        if (temp_4 != NULL) {
            EffObjStepChannels_1a9b50(temp_4, var_20, fparg0);
            if (!(temp_18->unk0 == NULL)) {
                XformPairComposeOffset_19a010(var_20, var_20 + 0xD0, (u8 *) arg2->unkC4 + (*(s32 *) ((u8 *) temp_18->unk0 + 0x14) * 0x120) + 0xD0);
            } else {
                XformPairComposeOffset_19a010(var_20, var_20 + 0xD0, spA0);
            }
            var_22 += EffInstNodeUpdateEmitters_19b430(temp_18->unkC, fparg0, arg1, var_20, var_20 + 0xD0);
        }
        var_19 += 1;
        var_21 += 0x1;
        var_20 += 0x120;
    }
    return var_22;
}
