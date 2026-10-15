#include "types.h"

struct T3036A0 { u8 pad000[0x180]; s32 f180; s32 f184; };

extern s32 TargetRefIsValid_2e6e40(u8 *a);

s32 EvDoorObjIsTargetActive_3036a0(struct T3036A0 *p)
{
    if (TargetRefIsValid_2e6e40((u8 *)p + 0xA0) == 0) return 0;
    if (p->f180 == 0) return 0;
    return p->f184 != 0;
}
