#include "types.h"

extern s32 StateFlagSet_3ccb70(void *, s16, s32, s32);
extern s16 *TableFindByName_4223f0(s32);

s32 StateFlagSetByName_3ccaf0(void *self, s32 unused1, s32 a2, s32 a3)
{
    void *p;
    s16 *q;

    p = *(void **)((u8 *)self + 4);
    if (p == NULL) {
        return 0;
    }
    q = TableFindByName_4223f0(*(s32 *)((u8 *)p + 0xC));
    if (q != NULL) {
        return StateFlagSet_3ccb70(self, *q, a2, a3);
    }
    return 0;
    return StateFlagSet_3ccb70(self, *q, a2, a3);
}
