#include "types.h"

struct G { u8 pad000[0x10]; s32 m10; };

extern s32 StateGetChapterIndexMaybe_3cd500(s32);
extern struct G *D_004837C0;

s32 PlayStatSetLevelMaybe_3a1c20(s32 p0, s32 p1, s32 p2)
{
    s32 r;
    s32 off;

    if (p1 >= 0) {
        if (p1 < 0xA) goto ok;
    }
    return 0;
ok:
    r = StateGetChapterIndexMaybe_3cd500(D_004837C0->m10);
    off = r * 10;
    *(u8 *)(p1 + (off + p0) + 0x24A) = (u8)p2;
    return 1;
}
