#include "types.h"

struct U19F430 { u8 pad000[0x78]; s32 f78; };
struct S19F430 { u8 pad000[0x24]; struct U19F430 *f24; };

extern s32 VariantGetInt_15f780(void);

s32 EffDefCmdEffectPreLoop_19f430(s32 a0, s32 a1, struct S19F430 **pp)
{
    struct S19F430 *s;

    s = *pp;
    s->f24->f78 = VariantGetInt_15f780();
    return 1;
}
