#include "types.h"

extern void EvObjCtor_2f9f00(void *);
extern void EvMapObjPointReset_3644f0(void *);
extern void EvMapObjPartInit_364240(void *);
extern void EvMapObjResetMaybe_366f20(void *);
extern s32 D_00471EC0[];   /* %hi/%lo -> incomplete array */

void *EvMapObjCtor_367040(u8 *o)
{
    u8 *p;

    EvObjCtor_2f9f00(o);
    *(s32 **)(o + 0xDC) = D_00471EC0;
    p = o + 0xE0;
    do {
        EvMapObjPointReset_3644f0(p);
        p += 0x40;
    } while (p < o + 0x1A0);
    EvMapObjPartInit_364240(o + 0xE0);
    EvMapObjResetMaybe_366f20(o);
    return o;
}
