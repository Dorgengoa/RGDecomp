#include "types.h"

struct T210070 { u8 pad000[0xA32]; s16 fA32; u8 padA34[0x10]; u32 fA44; };

s32 CharaIsLocoModeMaybe_210070(struct T210070 *p)
{
    if ((p->fA44 & 0x100) != 0) {
        return 0;
    }
    return (u32)p->fA32 < 6;
}
