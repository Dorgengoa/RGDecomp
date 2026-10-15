#include "types.h"

extern s32 StreamChanIsActive_1d7210(s32);
extern s32 StreamChanIsOpenReq_1d7290(s32);
extern s32 StreamChanGetName_1d72b0(s32);
extern s32 strcmp(s32, s32);

s32 StreamMgrChanIsActive_1d6540(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;

    if ((arg1 < 0) || (arg1 >= 4)) {
        return 0;
    }
    temp_16 = arg0 + (arg1 * 0xE0);
    if ((StreamChanIsOpenReq_1d7290(temp_16) == 0) && (StreamChanIsActive_1d7210(temp_16) == 0)) {
        return 0;
    }
    if ((arg2 != 0) && (strcmp(StreamChanGetName_1d72b0(temp_16), arg2) != 0)) {
        return 0;
    }
    return 1;
}
