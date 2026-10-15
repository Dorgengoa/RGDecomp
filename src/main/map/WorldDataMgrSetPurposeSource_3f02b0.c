#include "types.h"

extern void WorldDataRequestInit_3f4060(void *);

/* Store order is the listing's: 0x0, 0x2, 0x10, 0xC (the `addiu $2,$0,1`
   return value is scheduled between the last two). */

s32 WorldDataMgrSetPurposeSource_3f02b0(u8 *self, s16 a, s32 b, s32 c)
{
    u8 *o;

    o = *(u8 **)(self + 0x28);
    if (o == 0) {
        return 0;
    }
    WorldDataRequestInit_3f4060(o);
    *(s16 *)(o + 0x00) = a;
    *(s16 *)(o + 0x02) = 3;
    *(s32 *)(o + 0x10) = b;
    *(s32 *)(o + 0x0C) = c;
    return 1;
}
