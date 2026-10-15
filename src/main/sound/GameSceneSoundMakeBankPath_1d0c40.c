/* PARK: m2c cannot decompile -- "Found jr instruction ... but the
   corresponding jump table is not provided." Needs a jump-table
   reconstruction pass this lane's budget does not cover. Not attempted. */
/* s49m: MATCH jtbl rodata_check */
#include "types.h"

extern s32 SoundSyPathFormat_1d22f0(u8 *arg0, s32 arg1);
extern s32 SoundBsPathFormat_1d22e0(u8 *arg0, s32 arg1);
extern s32 SoundSrPathFormat_1d22d0(u8 *arg0, s32 arg1);
extern s32 SoundObPathFormat_1d22c0(u8 *arg0, s32 arg1);
extern s32 SoundFgPathFormat_1d22b0(u8 *arg0, s32 arg1);
extern s32 SoundEventPathFormat_1d2290(u8 *arg0, s32 arg1, s32 arg2);

s32 GameSceneSoundMakeBankPath_1d0c40(s32 arg0, u8 *arg1, s8 arg2, s32 arg3, s32 arg4)
{
    s32 ret;

    ret = -1;
    *arg1 = 0;
    if (arg3 < 0 || arg3 >= 1000) {
        goto end;
    }
    if (arg4 < 0 || arg4 >= 1000) {
        goto end;
    }
    switch (arg2) {
    case 0:
        SoundSyPathFormat_1d22f0(arg1, arg4);
        ret = arg4;
        break;
    case 1:
        SoundBsPathFormat_1d22e0(arg1, arg4);
        ret = arg4;
        break;
    case 2:
        SoundSrPathFormat_1d22d0(arg1, arg4);
        ret = arg4;
        break;
    case 3:
        SoundSrPathFormat_1d22d0(arg1, arg4);
        ret = arg4;
        break;
    case 4:
        SoundObPathFormat_1d22c0(arg1, arg4);
        ret = arg4;
        break;
    case 5:
        SoundFgPathFormat_1d22b0(arg1, arg4);
        ret = arg4;
        break;
    case 6:
        SoundEventPathFormat_1d2290(arg1, arg3, arg4);
        ret = arg4 + arg3 * 1000;
        break;
    }
end:
    return ret;
}
