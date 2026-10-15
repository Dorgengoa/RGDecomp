#include "types.h"

extern void ScriptSetRefInt_26a1e0(s32, s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern void *GetAbilityReq_27a640(void);
extern s32 EquipSlotGetRecId_3a0760(s32);

s32 EvCmdAbilityReqGet_260220(s64 *arg0) {
    s32 temp_17;
    s32 temp_4;
    void *temp_2;

    temp_2 = GetAbilityReq_27a640();
    if (temp_2 == NULL) {
        return 0;
    }
    switch (ScriptGetInt_26a2a0((s32)arg0++)) {
        case 0:
            ScriptSetRefInt_26a1e0((s32)arg0, *(s32 *)((u8 *)temp_2 + 0));
            break;
        case 1:
            temp_4 = *(s32 *)((u8 *)temp_2 + 8);
            if (temp_4 == 0) {
                return 0;
            }
            ScriptSetRefInt_26a1e0((s32)arg0, EquipSlotGetRecId_3a0760(temp_4));
            break;
        default:
            break;
    }
    return 1;
}
