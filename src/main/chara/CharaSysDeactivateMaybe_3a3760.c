#include "types.h"

typedef struct BF3a3760 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 3;
} BF3a3760;

extern void CharaStateReset_3a79b0(s32, s32, s32, s32, s32);

void CharaSysDeactivateMaybe_3a3760(void *self)
{
    u8 *p = (u8 *)self;
    s32 v;
    s32 t4;

    v = 0;
    ((BF3a3760 *)(p + 0x24C))->b0 = v;
    ((BF3a3760 *)(p + 0x24C))->b1 = v;
    ((BF3a3760 *)(p + 0x24C))->b2 = v;
    ((BF3a3760 *)(p + 0x24C))->b4 = v;
    t4 = *(s32 *)(p + 0x238);
    if (t4 != 0) {
        CharaStateReset_3a79b0(t4, 0, 1, 1, 1);
    }
}
