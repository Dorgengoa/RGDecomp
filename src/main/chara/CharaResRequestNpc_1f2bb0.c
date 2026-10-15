#include "types.h"

extern s32 CharaDataFindById_1ed990(s32 arg0, s32 arg1);
extern s32 CharaNpcResRequest_1f1600(s32 arg0, s32 arg1);
extern s32 CharaResRequest_1f2d90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern s32 NpcDefGetCharaDataId_1f5000(s32 arg0);
extern s32 GetCharaDataMgr_1fdb70(void);

s32 CharaResRequestNpc_1f2bb0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_22;
    s32 temp_2;
    s32 flag;

    temp_22 = GetCharaDataMgr_1fdb70();
    temp_2 = NpcDefGetCharaDataId_1f5000(arg3);
    if (temp_2 == -1) {
        return 0;
    }
    flag = 1;
    if ((arg4 == 1) && (CharaDataFindById_1ed990(temp_22, temp_2) == 0) && (CharaNpcResRequest_1f1600(arg0, arg3) == 0)) {
        return 0;
    }
    return CharaResRequest_1f2d90(arg0, arg1, arg2, arg3, temp_2, flag, flag);
}
