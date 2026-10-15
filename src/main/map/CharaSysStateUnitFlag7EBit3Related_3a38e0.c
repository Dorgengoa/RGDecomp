#include "types.h"
struct A3a38e0 { u8 pad000[0x7E]; s8 f0 : 3; s8 f3 : 1; };
struct B3a38e0 { u8 pad000[0x18]; struct A3a38e0 *m18; };
struct S3a38e0 { u8 pad000[0x238]; struct B3a38e0 *m238; };

s32 CharaSysStateUnitFlag7EBit3Related_3a38e0(struct S3a38e0 *p)
{
    struct A3a38e0 *t;

    if (p->m238 != 0) {
        t = p->m238->m18;
    } else {
        t = 0;
    }
    if (t == 0) {
        return 1;
    }
    return t->f3 != 0;
}
