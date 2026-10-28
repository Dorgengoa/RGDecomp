/* rgp:protos */
#define RGP_SELF_MotionEntryLoadAmixer_1738e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MotionEntryLoadAmixer_1738e0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 sp5C;
    s32 temp_2;

    temp_2 = ((s32)ArchiveGetFileData_181dd0(arg1, arg2, &sp5C));
    if (temp_2 == 0) {
        return 0;
    }
    AmixerInit_170dd0(arg0 + 0xC);
    AmixerCfgParseThunk_1700d0(arg0 + 0xC, temp_2, sp5C, arg3);
    return AmixerBindResByNameMaybe_170330(arg0 + 0xC, arg1, arg3, 1);
}
