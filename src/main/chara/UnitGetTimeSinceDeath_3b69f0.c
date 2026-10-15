#include "types.h"

extern void *D_00483818;
extern s32 DoubleToUInt_13bb78(s64);

s32 UnitGetTimeSinceDeath_3b69f0(void *self)
{
    s32 count;
    s32 diff;
    void *p;
    s32 total;

    if (D_00483818 == NULL) {
        return -1;
    }
    count = *(s32 *)((u8 *)self + 0x198);
    if (count <= 0) {
        return -1;
    }
    p = *(void **)((u8 *)D_00483818 + 0x20);
    p = *(void **)((u8 *)p + 0x238);
    if (p != NULL) {
        total = DoubleToUInt_13bb78(*(s64 *)((u8 *)p + 0x178));
    } else {
        total = 0;
    }
    diff = total - count;
    if (diff < 0) {
        return -1;
    }
    return diff;
}
