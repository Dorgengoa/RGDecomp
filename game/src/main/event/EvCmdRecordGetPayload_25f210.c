/* rgp:protos */
#define RGP_SELF_EvCmdRecordGetPayload_25f210 1
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
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdRecordGetPayload_25f210(s32 arg0, s32 arg1)
{
    s32 *temp_2_2;
    s32 temp_3;
    s32 var_17;
    u8 *temp_2;
    u8 *temp_4;

    var_17 = arg0;
    temp_4 = *(u8 **)((u8 *)GetGameData_1fede0() + 0x24);
    temp_3 = *(s32 *)(*(u8 **)(temp_4 + 0x1188) + 0x4);
    switch (temp_3) {
        case 0x14:
            temp_2 = (u8 *)RecordGetPayloadIfKind14_430b90(temp_4);
            if (temp_2 != NULL) {
                if (arg1 > 0) {
                    s32 temp_4_2 = var_17;
                    var_17 += 8;
                    ScriptSetRefInt_26a1e0(temp_4_2, *(s32 *)(temp_2 + 0x0));
                }
                if (arg1 >= 2) {
                    ScriptSetRefInt_26a1e0(var_17, *(s32 *)(temp_2 + 0x4));
                }
            }
            break;
        case 0x1E:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind1E_430b70(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
        case 0x28:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind28_430b50(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
        case 0x32:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind32_430b30(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
        case 0x3C:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind3C_430b10(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
        case 0x3D:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind3D_430af0(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
        case 0x3E:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind3E_430ad0(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
        case 0x3F:
            temp_2_2 = ((s32 *)RecordGetPayloadIfKind3F_430ab0(temp_4));
            if ((temp_2_2 != NULL) && (arg1 > 0)) {
                ScriptSetRefInt_26a1e0(var_17, *temp_2_2);
            }
            break;
    }
    return 1;
}
