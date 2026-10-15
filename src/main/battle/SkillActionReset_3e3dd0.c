#include "types.h"

extern void *memset(void *, s32, s32);

/* memset then the tail fields; the one-bit field at 0x40 assigned 0.
   Store order is retail's: 0x0, 0x3C, 0x44, 0x3E, bitfield. */

typedef struct {
    s16 m00;
    u8 pad02[0x3A];
    s16 m3C;
    s16 m3E;
    u32 b0 : 1;
    s32 m44;
} S3DD0;

void SkillActionReset_3e3dd0(S3DD0 *p)
{
    memset(p, 0, 0x3C);
    p->m00 = -1;
    p->m3C = -1;
    p->m44 = 0;
    p->m3E = 0;
    p->b0 = 0;
}
