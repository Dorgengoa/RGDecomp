#include "types.h"

typedef struct {
    u8 pad0[0x70];
    s32 unk70;
} Obj003A5010;

extern s32 CharaSysEncounterPickFormationMaybe_3a5090(s32, s32, s64, s32, s32);
extern s32 GroupGetRecordById_402240(s32, s64, s64);
extern Obj003A5010 *D_004837C4;

s32 CharaSysEncounterStartGroupMaybe_3a5010(s32 arg0, s64 arg1, s64 arg2, s32 arg3, s32 arg4) {
    s32 temp_2;

    temp_2 = GroupGetRecordById_402240(D_004837C4->unk70, (s64)(s16)arg1, (s64)(s16)arg2);
    if (temp_2 != 0) {
        return CharaSysEncounterPickFormationMaybe_3a5090(arg0, temp_2, arg1, arg3, arg4);
    }
    return 0;
}
