#include "types.h"

extern void VecCopy_1cbe30(void *dst, void *src);

s32 CharaHangLedgeGetNormal_23a1f0(u8 *base, void *dst, s32 i)
{
    if (i < 0) goto fail;
    if (i < 2) goto ok;
fail:
    return 0;
ok:
    VecCopy_1cbe30(dst, base + i * 16 + 0x40);
    return 1;
}
