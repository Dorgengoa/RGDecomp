/* rgp:protos */
#define RGP_SELF_RecordGetPayloadIdsMaybe_430940 1
#include "port/game_protos.h"
#line 1
/* PARK 3/3: RIGHT LENGTH (89w), 8 bad, ALL the same class of residue as HandleEntryRelease_3f1d80 (var_16=1 wants daddiu not addiu) repeated 8 times (once per if-block). Same `s64 var_16` experiment fixes the instruction form but breaks length; needs the same follow-up. */
#include "types.h"

typedef struct Pair {
    s32 unk0;
    s32 unk4;
} Pair;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u16 RecordGetPayloadIdsMaybe_430940(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 *temp_2_2;
    s32 *temp_2_3;
    s32 *temp_2_4;
    s32 *temp_2_5;
    s32 *temp_2_6;
    s32 *temp_2_7;
    s32 *temp_2_8;
    u16 var_16;
    Pair *temp_2;

    *arg1 = -1;
    var_16 = 0;
    *arg2 = -1;
    *arg3 = -1;
    temp_2 = ((Pair *)RecordGetPayloadIfKind14_430b90((void *)arg0));
    if (temp_2 != NULL) {
        var_16 = 1;
        *arg1 = temp_2->unk0;
        *arg2 = temp_2->unk4;
    }
    temp_2_2 = ((s32 *)RecordGetPayloadIfKind1E_430b70(arg0));
    if (temp_2_2 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_2;
    }
    temp_2_3 = ((s32 *)RecordGetPayloadIfKind28_430b50(arg0));
    if (temp_2_3 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_3;
    }
    temp_2_4 = ((s32 *)RecordGetPayloadIfKind32_430b30(arg0));
    if (temp_2_4 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_4;
    }
    temp_2_5 = ((s32 *)RecordGetPayloadIfKind3C_430b10(arg0));
    if (temp_2_5 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_5;
    }
    temp_2_6 = ((s32 *)RecordGetPayloadIfKind3D_430af0(arg0));
    if (temp_2_6 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_6;
    }
    temp_2_7 = ((s32 *)RecordGetPayloadIfKind3E_430ad0(arg0));
    if (temp_2_7 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_7;
    }
    temp_2_8 = ((s32 *)RecordGetPayloadIfKind3F_430ab0(arg0));
    if (temp_2_8 != NULL) {
        var_16 = 1;
        *arg3 = *temp_2_8;
    }
    return var_16;
}
