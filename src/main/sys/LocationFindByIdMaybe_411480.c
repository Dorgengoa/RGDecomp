#include "types.h"

extern s32 GroupRangeLookup_411590(void);
extern s32 GroupRangeLookup_411500(void *, void *, s32);

s32 LocationFindByIdMaybe_411480(void *a, void *b, s32 c)
{
    s32 r;
    if ((s16)c < 0) return 0;
    r = GroupRangeLookup_411590();
    if (r != 0) return r;
    r = GroupRangeLookup_411500(a, b, c);
    if (r != 0) {
        return r;
    }
    return 0;
}
