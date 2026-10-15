#include "types.h"

extern s32 GroupFindByKey_4256c0(void *arg0, s32 arg1);
extern s32 GroupSubEntryFindNth_425e10(s32 arg0, s32 arg1, s32 arg2);

s32 GroupFindSubEntryNth_425520(void *arg0, s64 arg1, s32 arg2, s32 arg3)
{
    s32 temp_2;

    if (*(s32 *)((u8 *)arg0 + 0x8) == 0) {
        return 0;
    }
    temp_2 = GroupFindByKey_4256c0(arg0, (s32)(s16)arg1);
    if (temp_2 != 0) {
        return GroupSubEntryFindNth_425e10(temp_2, arg2, arg3);
    }
    return 0;
}
