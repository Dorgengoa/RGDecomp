#include "types.h"

extern void *GroupTableFindEntry_422950(s32 arg0, s16 arg1, s16 arg2);

s16 ProgressValueGet_3cd2c0(void *arg0, s64 arg1, s64 arg2)
{
    void *inner;
    void *result;
    s16 idx;

    inner = *(void **)((u8 *)arg0 + 4);
    if (inner == NULL) {
        return -1;
    }
    result = GroupTableFindEntry_422950(*(s32 *)((u8 *)inner + 8), (s16)arg1, (s16)arg2);
    if (result != NULL) {
        idx = *(s16 *)((u8 *)result + 8);
        return ((s16 *)((u8 *)arg0 + 0xA))[idx];
    }
    return -1;
}
