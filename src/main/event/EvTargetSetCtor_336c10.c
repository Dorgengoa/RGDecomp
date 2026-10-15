#include "types.h"

extern void TargetRefCtor_2e71f0(s32);
extern void XformCtor_2e79c0(s32);
extern void EvTargetSetReset_336bb0(s32);

s32 EvTargetSetCtor_336c10(s32 p0)
{
    u8 *l2;

    TargetRefCtor_2e71f0(p0);
    TargetRefCtor_2e71f0((p0 + 0x30));
    l2 = (u8 *)p0 + 0x60;
    do {
        TargetRefCtor_2e71f0((s32)l2);
        l2 = l2 + 0x30;
    } while (l2 < (u8 *)p0 + 0xC0);
    XformCtor_2e79c0(p0 + 0xC0);
    EvTargetSetReset_336bb0(p0);
    return p0;
}
