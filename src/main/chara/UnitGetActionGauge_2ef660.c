#include "types.h"

struct T2EF660 { u8 pad000[0x1C4]; f32 f1C4; };

s32 UnitGetActionGauge_2ef660(struct T2EF660 *p)
{
    return (s32)p->f1C4;
}
