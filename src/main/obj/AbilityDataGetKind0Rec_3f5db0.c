#include "types.h"

struct T3F5DB0 { u8 pad000[0x2]; u8 f2; u8 pad003[0x9]; s32 fC; };

s32 AbilityDataGetKind0Rec_3f5db0(struct T3F5DB0 *p)
{
    s32 v;

    if (p->f2 == 0) {
        v = p->fC;
        if (v != 0) {
            return v;
        }
    }
    return 0;
}
