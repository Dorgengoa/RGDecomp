#include "types.h"

struct T3A9800 { u8 pad000[0x8]; s32 f08; u8 pad00C[0x4B4]; u8 f4C0_b0 : 1; u8 f4C0_r : 7; };

extern "C" bool CharaKind1002ResetState_3a99a0(struct T3A9800 *p);

extern "C" s32 CharaKind1003ResetState_3a9800(struct T3A9800 *p)
{
    bool r;

    r = CharaKind1002ResetState_3a99a0(p);
    if (r == 0) return 0;
    p->f08 = 0x3EB;
    p->f4C0_b0 = 0;
    return 1;
}
