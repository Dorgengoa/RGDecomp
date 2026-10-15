#include "types.h"

extern u8 *EffectFindByNameNoId_2dfed0(void);

s32 EffectEntryIsLoadedByName_2de700(void)
{
    u8 *r;
    u8 *q;

    r = EffectFindByNameNoId_2dfed0();
    if (r != 0) goto g1;
    return 0;
g1:
    q = r + 0xC;
    if (q != 0) {
        if (*(s16 *)(q + 0xA) != 1) return 0;
        return *(s16 *)(q + 0xC) == 1;
    }
    return 0;
}
