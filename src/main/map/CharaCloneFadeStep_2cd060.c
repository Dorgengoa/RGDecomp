#include "types.h"

extern void ParamTableSetAlpha_1cfb10(s32 arg0, s32 arg1, f32 arg2);
extern f32 ParamTableGetAlpha_1cfb40(s32 arg0, s32 arg1);
extern s32 CharaDataFindNode_1ed6d0(s32 arg0, s16 arg1, s32 arg2, s32 arg3);
extern s32 CharaDataNodeGetSubObj_1eeb30(s32 arg0, s32 arg1);
extern s32 CharaDataNodeGetSubObjCount_1eeb80(s32 arg0);
extern void *CharaResFindById_1f0530(s32 arg0, s32 arg1);
extern s32 GetCharaResMgr_1fdb60(void);
extern s32 GetCharaDataMgr_1fdb70(void);
extern void CharaCloneRelease_2cced0(s32 arg0);
extern s32 D_0047EDD0;
extern s32 D_0047EDD4;
extern f32 D_004825D8;

void CharaCloneFadeStep_2cd060(s32 arg0)
{
    f32 temp_f0;
    f32 temp_f1;
    s32 temp_17;
    s32 temp_17_2;
    s32 temp_2_2;
    s32 temp_2_3;
    void *temp_2;

    if (D_0047EDD0 > 0) {
        temp_17 = GetCharaResMgr_1fdb60();
        temp_17_2 = GetCharaDataMgr_1fdb70();
        temp_2 = CharaResFindById_1f0530(temp_17, D_0047EDD4);
        if (temp_2 == NULL) {
            CharaCloneRelease_2cced0(arg0);
        } else {
            temp_2_2 = CharaDataFindNode_1ed6d0(temp_17_2, *(s16 *)((u8 *)temp_2 + 0x4), 0, 0);
            if (temp_2_2 == 0) {
                CharaCloneRelease_2cced0(arg0);
            } else {
                if (CharaDataNodeGetSubObjCount_1eeb80(temp_2_2) <= 0) {
                    CharaCloneRelease_2cced0(arg0);
                } else {
                    if (CharaDataNodeGetSubObj_1eeb30(temp_2_2, 0) == 0) {
                        CharaCloneRelease_2cced0(arg0);
                    } else {
                        temp_f0 = ParamTableGetAlpha_1cfb40(arg0, 0x9C);
                        temp_f1 = temp_f0 + ((D_004825D8 - temp_f0) / (f32)D_0047EDD0);
                        D_0047EDD0 = D_0047EDD0 - 1;
                        if (D_0047EDD0 <= 0) {
                            ParamTableSetAlpha_1cfb10(arg0, 0x9C, D_004825D8);
                            CharaCloneRelease_2cced0(arg0);
                            return;
                        }
                        ParamTableSetAlpha_1cfb10(arg0, 0x9C, temp_f1);
                    }
                }
            }
        }
    }
}
