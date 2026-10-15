#include "types.h"

extern s32 ModelGetRootFrame_1511a0(s32);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s8 *);
extern s32 GetLiveObjById_1ce420(void);

s32 GetObjNodeByName_1ce3a0(s32 arg0, s32 arg1, s8 *arg2)
{
    s32 temp_2;

    temp_2 = GetLiveObjById_1ce420();
    if (temp_2 == 0) {
        return 0;
    }
    if ((arg2 != NULL) && (*arg2 != 0)) {
        return ModelGetFrame_1511f0(temp_2, ModelFindFrameIndexByName_151220(temp_2, arg2));
    }
    return ModelGetRootFrame_1511a0(temp_2);
}
