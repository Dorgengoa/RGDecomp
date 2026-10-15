#include "types.h"
struct A3F5CD0 { u8 pad000[0x8]; s8 f08_b : 5; s8 f08_r : 3; };
struct R3F5CD0 { u8 pad000[0x10]; struct A3F5CD0 *f10; };
extern struct R3F5CD0 *AbilityDataGetKind0Rec_3f5db0(void);

s32 AbilityDataGetEffectTargetKind_3f5cd0(void)
{
    struct R3F5CD0 *r;
    struct A3F5CD0 *q;

    r = AbilityDataGetKind0Rec_3f5db0();
    if (r == 0) return -1;
    q = r->f10;
    if (q != 0) {
        return q->f08_b;
    }
    return -1;
}
