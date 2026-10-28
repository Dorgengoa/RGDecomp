/* rgp:protos */
#define RGP_SELF_HandleEntryRelease_3f12f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 HandleEntryRelease_3f12f0(s32 arg0, void *arg1, s32 arg2)
{
    s32 temp_2;

    if (arg1 == NULL) {
        return 0;
    }
    if (arg2 != 0) {
        HandleEntryFreeRes_3f1420((int)arg0, (void *)arg1);
    }
    temp_2 = ((s32)MemStackArrayGet_3f15a0(arg0, *(s16 *)((u8 *)arg1 + 0xC)));
    if (temp_2 != 0) {
        MemStackReset_14d830(temp_2);
    }
    if (arg2 != 0) {
        HandleEntryInit_3f40a0(arg1);
    }
    return 1;
}
