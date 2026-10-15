#include "types.h"

extern void CharaDataReleaseById_1ed850(s32, s32);
extern s32 CharaDataFindById_1ed990(s32, s32);
extern s32 CharaDataCreate_1edab0(s32, s32 *);
extern s32 PcDefGetCharaDataId_1f5060(s32);
extern s32 IsPcCharaId_1f52d0(s32);
extern s32 GetCharaDataMgr_1fdb70(void);

s32 CharaDataEnsureLoaded_1f0d00(s32 arg0, s32 arg1) {
    s32 sp[10];
    s32 temp_16;
    s32 temp_2;
    s32 temp_5;
    s32 var_4;

    if (IsPcCharaId_1f52d0(arg1) == 0) {
        return 0;
    }
    temp_16 = GetCharaDataMgr_1fdb70();
    temp_2 = PcDefGetCharaDataId_1f5060(arg1);
    if (CharaDataFindById_1ed990(temp_16, temp_2 - 0x3DD) != 0) {
        return 1;
    }
    var_4 = 0;
    sp[0] = -1;
    sp[1] = -1;
    do {
        sp[2 + var_4] = -1;
        var_4 += 1;
    } while (var_4 < 7);
    temp_5 = temp_2 - 0x3DD;
    sp[1] = 1;
    sp[0] = temp_5;
    sp[9] = 0x3900;
    sp[6] = 0x3898;
    CharaDataReleaseById_1ed850(temp_16, temp_5);
    return CharaDataCreate_1edab0(temp_16, &sp[0]) != 0;
}
