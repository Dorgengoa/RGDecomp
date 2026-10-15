#include "types.h"

struct T1A9E40 { u8 pad000[0x8]; s32 f08; };
struct U1A9E40 { u8 pad000[0x8]; s32 f08; u8 pad00C[0xA8]; void *fB4; };

extern void *MemStackNew_14e1b0(s32 n);

s32 EffObjAllocWorkSlots_1a9e40(struct T1A9E40 *p, void *unused, struct U1A9E40 *o)
{
    s32 n;
    void *r;

    n = p->f08;
    r = MemStackNew_14e1b0(n * 16);
    o->f08 = n;
    o->fB4 = r;
    if (r != 0) goto one;
    if (n <= 0) goto one;
    return 0;
one:
    return 1;
}
