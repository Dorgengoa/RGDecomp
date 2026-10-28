/* rgp:protos */
#define RGP_SELF_GaijiLoadImage_2705a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0045F688[];
extern u8 D_004C3180[];
/*rgp*/
extern void *memcpy(void *, void *, u32);

s32 GaijiLoadImage_2705a0(void *a)
{
    s32 len = 0;
    void *r = ArchiveGetFileByPath_1c2800(a, D_0045F688, &len);
    if (r == 0) goto zero;
    if (len > 0) {
        if ((u32)len <= 0x10800) goto ok;
    }
zero:
    return 0;
ok:
    memcpy(D_004C3180, r, len);
    return len;
}
