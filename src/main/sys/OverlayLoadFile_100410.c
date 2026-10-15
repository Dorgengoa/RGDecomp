#include "types.h"

extern s32 FileReadAll_1004b0(s32 a, void *h);
extern void OverlayLoadNotifyStubMaybe_100400(void *h);
extern void FlushCache(s32 op);
extern void *memset(void *p, s32 c, u32 n);
extern void RunStaticCtors_100df0(s32 a, s32 b, s32 c, s32 d);

s32 OverlayLoadFile_100410(s32 a, u8 *h)
{
    u32 r = 0;
    s32 n;

    n = FileReadAll_1004b0(a, h);
    if (n > 0) {
        OverlayLoadNotifyStubMaybe_100400(h);
        r = *(u32 *)(h + 0x14);
        FlushCache(0);
        FlushCache(2);
        if (r != 0)
            memset(h + n, 0, r);
        RunStaticCtors_100df0(*(s32 *)(h + 0x18), *(s32 *)(h + 0x1c), 0, 0);
        r = 1;
    }
    return r;
}
