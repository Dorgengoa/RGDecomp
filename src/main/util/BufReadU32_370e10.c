#include "types.h"

extern void *memcpy(void *, const void *, u32);

s32 BufReadU32_370e10(void *a, u32 n, void *dst)
{
    if (a == 0) goto fail;
    if (n >= 4) goto ok;
fail:
    return 0;
ok:
    memcpy(dst, a, 4);
    return 4;
}
