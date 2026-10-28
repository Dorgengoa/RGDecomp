/* rgp:protos */
#define RGP_SELF_WorldDataMgrZoneEntryLink_3f1ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldDataMgrZoneEntryLink_3f1ef0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;

    if (arg1 == 0) {
        return 0;
    }
    temp_4 = *(s32 *)((u8 *)arg0 + 0x6C);
    if (temp_4 != 0 && (arg2 == 1 || arg2 < 0)) {
        WorldSubsysZoneEntryLink_41c480(temp_4, arg1);
    }
    temp_4_2 = *(s32 *)((u8 *)arg0 + 0x80);
    if (temp_4_2 != 0 && (arg2 == 2 || arg2 < 0)) {
        WorldSubsysZoneEntryLink_41e340(temp_4_2, arg1);
    }
    temp_4_3 = *(s32 *)((u8 *)arg0 + 0x78);
    if (temp_4_3 != 0 && (arg2 == 3 || arg2 < 0)) {
        WorldSubsysZoneEntryLink_426f90(temp_4_3, arg1);
    }
    return 1;
}
