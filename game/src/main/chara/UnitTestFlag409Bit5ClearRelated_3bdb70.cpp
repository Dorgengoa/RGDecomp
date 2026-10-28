#include "types.h"

struct T3BDB70 { u8 pad000[0x409]; u8 f409_b0 : 1; u8 f409_b1 : 1; u8 f409_b2 : 1; u8 f409_b3 : 1; u8 f409_b4 : 1; u8 f409_b5 : 1; u8 f409_r : 2; };

extern "C" s32 UnitTestFlag409Bit5ClearRelated_3bdb70(struct T3BDB70 *p)
{
    s32 t;
    bool b;

    t = p->f409_b5;
    b = t;
    return b ^ 1;
}
