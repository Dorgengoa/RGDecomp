#include "types.h"

extern void *memcpy(void *, const void *, s32);

/* Same object as SkillActionReset_3e3dd0 but copy-constructed.  0x20 is stored before
   0x10..0x1C in the listing, so that is the source order too. */

typedef struct {
    u8 pad00[0xA];
    s16 m0A;
    u8 pad0C[0x4];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    u8 pad24[0x18];
    s16 m3C;
    s16 m3E;
    u32 b0 : 1;
    s32 m44;
} S3D50;

void SkillActionInitFromDef_3e3d50(S3D50 *p, s16 a, const void *src)
{
    if (src == 0) {
        return;
    }
    memcpy(p, src, 0x3C);
    p->m0A = 0;
    p->m20 = 0;
    p->m10 = 0;
    p->m14 = 0;
    p->m18 = 0;
    p->m1C = 0;
    p->m3C = a;
    p->m3E = 0;
    p->m44 = 0;
    p->b0 = 0;
}
